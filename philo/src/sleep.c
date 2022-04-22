/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 22:01:28 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/22 21:14:07 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include "philo.h"

/**
 * Sleep, rewritten for this project, in steps of ~500 microseconds to make
 * it more accurate
 * @param[in] time_ms The time to sleep, in milliseconds
 * @return Returns 1
 */
int	ph_sleep(unsigned int time_ms)
{
	unsigned int	init_timestamp;
	unsigned int	timestamp;

	get_time_in_ms(&init_timestamp);
	get_time_in_ms(&timestamp);
	while (timestamp < init_timestamp + time_ms)
	{
		usleep(500);
		get_time_in_ms(&timestamp);
	}
	return (1);
}
