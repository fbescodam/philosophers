/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   status.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/22 21:22:12 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/22 21:31:39 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

static void	stat_func_think(t_philo *philo, unsigned int *timestamp)
{
	printf("%6d %d is thinking\n", *timestamp, philo->id);
}

static void	stat_func_eat(t_philo *philo, unsigned int *timestamp)
{
	pthread_mutex_lock(&philo->last_ate_lock);
	get_time_in_ms(&philo->last_ate);
	pthread_mutex_unlock(&philo->last_ate_lock);
	printf("%6d %d is eating\n", *timestamp, philo->id);
}

static void	stat_func_sleep(t_philo *philo, unsigned int *timestamp)
{
	if (philo->sim->times_to_eat == UNLIMITED_TIMES_TO_EAT
		|| philo->times_eaten < philo->sim->times_to_eat)
		philo->times_eaten++;
	printf("%6d %d is sleeping\n", *timestamp, philo->id);
}

static void	stat_func_die(t_philo *philo, unsigned int *timestamp)
{
	printf("%6d %d died\n", *timestamp, philo->id);
}

/**
 * Set the philosopher status and print it.
 * @param[in] philo The philosopher struct
 * @param[in] status The new status of the philosopher
 */
void	set_n_print_status(t_philo *philo, enum e_status status)
{
	unsigned int	timestamp;
	static void		(*stat_funcs[4])(t_philo *philo, unsigned int *timestamp);

	if (!stat_funcs[thinking])
	{
		stat_funcs[thinking] = stat_func_think;
		stat_funcs[eating] = stat_func_eat;
		stat_funcs[sleeping] = stat_func_sleep;
		stat_funcs[dead] = stat_func_die;
	}
	get_time_in_ms(&timestamp);
	pthread_mutex_lock(&philo->sim->write_lock);
	philo->status = status;
	if (philo->sim->start == 0)
		philo->sim->start = timestamp;
	timestamp = timestamp - philo->sim->start;
	if (!philo->sim->stopped)
		(*(stat_funcs[status]))(philo, &timestamp);
	pthread_mutex_unlock(&philo->sim->write_lock);
}
