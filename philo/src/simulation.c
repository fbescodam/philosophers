/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 17:22:05 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/15 18:45:24 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Simulate a philosopher status (just call usleep and check if dead...)
 * @return Returns the return value of ph_sleep or < 0 on error
 */
int	simulate(t_philo *philo)
{
	unsigned int	sleep_time;

	if (philo->sim->stopped)
		return (2);
	if (philo->status == STATUS_DEAD)
	{
		philo->sim->stopped = 1;
		return (0);
	}
	else if (philo->status == STATUS_THINKING)
		sleep_time = philo->sim->time_to_die;
	else if (philo->status == STATUS_EATING)
	{
		if (get_time_in_ms(&philo->last_ate) != 0)
			return (-8);
		sleep_time = philo->sim->time_to_eat;
	}
	else if (philo->status == STATUS_SLEEPING)
		sleep_time = philo->sim->time_to_sleep;
	return (ph_sleep(philo, sleep_time));
}
