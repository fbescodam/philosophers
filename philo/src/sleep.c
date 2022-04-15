/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 22:01:28 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/16 01:32:14 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include "philo.h"

/**
 * Sleep, rewritten for this project, in steps of ~50 microseconds to make
 * it more accurate
 * @param[in] time_ms The time to sleep, in milliseconds
 * @return Returns 1 on success, 0 on error
 */
int	ph_sleep(unsigned int time_ms)
{
	useconds_t	wanted_time;
	useconds_t	total_time;
	useconds_t	time;

	wanted_time = time_ms * 1000;
	total_time = 0;
	while (total_time < wanted_time)
	{
		time = wanted_time - total_time;
		if (time > 50)
			time = 50;
		if (usleep(time) != 0)
			return (0);
		total_time += time;
	}
	return (1);
}
