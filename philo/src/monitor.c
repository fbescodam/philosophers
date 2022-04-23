/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitor.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/15 22:09:11 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/23 16:37:28 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "philo.h"

/**
 * Loop over all philosophers and check if they are "healthy" (have to die)
 * @param[in] sim		The simulation struct
 * @param[in] time		The current timestamp
 * @param[in] eat_sum	A pointer to the parameter where the sum of all
 * 						times_eatens are stored
 * @return				Returns 1 if simulation stopped, 0 otherwise
 */
static int	philo_doctor(t_sim *sim, unsigned int *time, int *eat_sum)
{
	t_list			*philo_li;
	t_philo			*philo;

	philo_li = sim->philos;
	while (philo_li)
	{
		philo = (t_philo *)philo_li->content;
		pthread_mutex_lock(&philo->last_ate_lock);
		*eat_sum += philo->times_eaten;
		if (*time > philo->last_ate
			&& *time - philo->last_ate > (unsigned int)sim->time_to_die)
		{
			pthread_mutex_unlock(&philo->last_ate_lock);
			simulate_status(philo, dead);
			return (1);
		}
		pthread_mutex_unlock(&philo->last_ate_lock);
		philo_li = philo_li->next;
	}
	return (0);
}

void	*start_monitor(void *sim_in_the_void)
{
	unsigned int	timestamp;
	int				times_eaten_sum;
	t_sim			*sim;

	sim = (t_sim *)sim_in_the_void;
	while (1)
	{
		get_time_in_ms(&timestamp);
		times_eaten_sum = 0;
		if (philo_doctor(sim, &timestamp, &times_eaten_sum))
			return ((void *) 0);
		if (sim->times_to_eat != UNLIMITED_TIMES_TO_EAT
			&& times_eaten_sum / sim->amount == sim->times_to_eat)
		{
			pthread_mutex_lock(&sim->status_lock);
			sim->stopped = 1;
			pthread_mutex_unlock(&sim->status_lock);
			return ((void *) 0);
		}
	}
	return ((void *)0);
}
