/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 22:01:28 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/15 18:28:31 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Sleep, rewritten for this project, where every ~50 microseconds,
 * a check will occur to check if the philosopher has died yet.
 * @param[in] philo A philosopher struct
 * @param[in] time_ms The time to sleep, in milliseconds
 * @return Returns 0 if died, 1 if not, 2 if simulation stopped
 */
int	ph_sleep(t_philo *philo, unsigned int time_ms)
{
	useconds_t	time_microsecs;
	useconds_t	i;
	useconds_t	incr;

	time_microsecs = time_ms * 1000;
	i = 50;
	while (i < time_microsecs)
	{
		if (philo->status == STATUS_DEAD)
			return (0);
		if (philo->sim->stopped)
			return (2);
		if (philo->status == STATUS_THINKING)
			decide_on_next_status(philo);
		incr = time_microsecs - i;
		if (incr > 50)
			incr = 50;
		if (usleep(incr) != 0)
			return (-1);
		i += incr;
	}
	decide_on_next_status(philo);
	return (1);
}
