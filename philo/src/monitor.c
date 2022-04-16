/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 22:09:11 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/16 04:54:20 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "philo.h"

void	*start_monitor(void *sim_in_the_void)
{
	unsigned int	timestamp;
	t_sim			*sim;
	t_list			*philo_li;
	t_philo			*philo;

	sim = (t_sim *)sim_in_the_void;
	if (usleep((sim->time_to_die - 10) * 1000) != 0)
		return ((void *)1);
	while (1)
	{
		if (!get_time_in_ms(&timestamp))
			return ((void *)1);
		philo_li = sim->philos;
		while (philo_li)
		{
			philo = (t_philo *)philo_li->content;
			if (pthread_mutex_lock(&philo->last_ate_lock) != 0)
				return (0);
			if (timestamp > philo->last_ate && timestamp - philo->last_ate > (unsigned int)sim->time_to_die + 3)
			{
				if (pthread_mutex_unlock(&philo->last_ate_lock) != 0)
					return (0);
				if (!set_n_print_status(philo, dead))
					return ((void *)1);
				philo->status = dead;
				if (pthread_mutex_lock(&philo->sim->write_lock) != 0)
					return (0);
				sim->stopped = 1;
				if (pthread_mutex_unlock(&philo->sim->write_lock) != 0)
					return (0);
				return ((void *)0);
			}
			if (pthread_mutex_unlock(&philo->last_ate_lock) != 0)
				return (0);
			philo_li = philo_li->next;
		}
	}
	return ((void *)0);
}