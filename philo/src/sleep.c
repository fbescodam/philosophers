/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sleep.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/08 22:01:28 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/16 03:56:01 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>
#include "philo.h"

/**
 * Sleep, rewritten for this project, in steps of ~500 microseconds to make
 * it more accurate
 * @param[in] time_ms The time to sleep, in milliseconds
 * @return Returns 1 on success, 0 on error
 */
int	ph_sleep(unsigned int time_ms)
{
	unsigned int	init_timestamp;
	unsigned int	timestamp;

	if (!get_time_in_ms(&init_timestamp))
		return (0);
	if (!get_time_in_ms(&timestamp))
		return (0);
	while (timestamp < init_timestamp + time_ms)
	{
		usleep(500);
		if (!get_time_in_ms(&timestamp))
			return (0);
	}
	return (1);
}
