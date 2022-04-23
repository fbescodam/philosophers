/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 19:19:19 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/23 17:45:38 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

/**
 * Simulate one day of a philosopher's life
 * @param[in] philo The philosopher to simulate
 */
static void	simulate(t_philo *philo)
{
	get_them_forks(philo);
	simulate_status(philo, eating);
	ph_sleep(philo->sim->time_to_eat);
	drop_them_forks(philo);
	simulate_status(philo, sleeping);
	ph_sleep(philo->sim->time_to_sleep);
	simulate_status(philo, thinking);
}

static void	*simulate_one(t_philo *philo)
{
	get_them_forks(philo);
	ph_sleep(philo->sim->time_to_die);
	drop_them_forks(philo);
	simulate_status(philo, dead);
	return ((void *)0);
}

/**
 * Start a philosopher's routine
 * @param philo	A struct containing the philosopher's details
 * @return		Returns NULL
 */
void	*start_routine(void *philo_in_the_void)
{
	t_philo		*philo;
	int			stopped;

	philo = (t_philo *)philo_in_the_void;
	if (philo->sim->amount == 1)
		return (simulate_one(philo));
	if (philo->sim->amount % 2 == 1)
		usleep(philo->id % 3 * 1000);
	else
		usleep(philo->id % 2 * 1000);
	pthread_mutex_lock(&philo->last_ate_lock);
	get_time_in_ms(&philo->last_ate);
	pthread_mutex_unlock(&philo->last_ate_lock);
	while (1)
	{
		pthread_mutex_lock(&philo->sim->status_lock);
		stopped = philo->sim->stopped;
		pthread_mutex_unlock(&philo->sim->status_lock);
		if (stopped)
			break ;
		simulate(philo);
	}
	return ((void *)0);
}
