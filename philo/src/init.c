/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/23 16:42:08 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/23 17:21:57 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include "philo.h"

static int	free_on_err(int err, void *freeable)
{
	if (freeable)
		free(freeable);
	return (err);
}

static int	init_philo(t_sim *sim, int i, t_philo *philo, t_list **elem_fork)
{
	philo->id = i + 1;
	philo->sim = sim;
	philo->last_ate = UINT_MAX;
	philo->times_eaten = 0;
	if (pthread_mutex_init(&philo->last_ate_lock, NULL) != 0)
		return (0);
	philo->fork_left = (t_fork *)(*elem_fork)->content;
	*elem_fork = (*elem_fork)->next;
	if (!*elem_fork)
		*elem_fork = sim->forks;
	philo->fork_right = (t_fork *)(*elem_fork)->content;
	return (1);
}

int	init_forks(t_sim *sim)
{
	int			i;
	t_fork		*fork;
	t_list		*elem_fork;

	i = 0;
	while (i < sim->amount)
	{
		fork = (t_fork *)malloc(sizeof(t_fork));
		if (!fork)
			return (-5);
		if (pthread_mutex_init(&fork->lock, NULL) != 0)
			return (free_on_err(-7, (void *)fork));
		elem_fork = ph_list_new((void *)fork);
		if (!elem_fork)
			return (free_on_err(-6, (void *)fork));
		ph_list_add(&sim->forks, elem_fork);
		i++;
	}
	return (0);
}

int	init_philos(t_sim *sim)
{
	int			i;
	t_list		*elem_fork;
	t_philo		*philo;
	t_list		*elem_philo;

	elem_fork = sim->forks;
	i = 0;
	while (i < sim->amount)
	{
		philo = (t_philo *)malloc(sizeof(t_philo));
		if (!philo)
			return (-1);
		if (!init_philo(sim, i, philo, &elem_fork))
			return (free_on_err(-7, (void *)philo));
		elem_philo = ph_list_new((void *)philo);
		if (!elem_philo)
			return (free_on_err(-2, (void *)philo));
		ph_list_add(&sim->philos, elem_philo);
		i++;
	}
	return (0);
}

int	start_threads(t_sim *sim)
{
	t_list		*elem_philo;

	if (pthread_create(&sim->monitor, NULL, &start_monitor, sim) != 0)
		return (-3);
	elem_philo = sim->philos;
	while (elem_philo)
	{
		if (pthread_create(&((t_philo *)elem_philo->content)->thread, NULL,
				&start_routine, elem_philo->content) != 0)
			return (-3);
		elem_philo = elem_philo->next;
	}
	pthread_join(sim->monitor, &sim->monit_ret);
	elem_philo = sim->philos;
	while (elem_philo)
	{
		pthread_join(((t_philo *)elem_philo->content)->thread,
			&((t_philo *)elem_philo->content)->ret);
		elem_philo = elem_philo->next;
	}
	return (0);
}
