/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 17:22:05 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/04 17:28:34 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

void	simulate(t_philo *philo)
{
	useconds_t	usecs;

	if (philo->status == STATUS_DEAD)
	{
		philo->sim->running = 0;
		return ;
	}
	else if (philo->status == STATUS_THINKING)
		usecs = 10;
	else if (philo->status == STATUS_EATING)
		usecs = philo->sim->time_to_eat;
	else if (philo->status == STATUS_SLEEPING)
		usecs = philo->sim->time_to_sleep;
	usleep(usecs);
	// decide_on_next_status(philo);
}
