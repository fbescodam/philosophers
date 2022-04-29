/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 17:21:44 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/29 21:12:34 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

/**
 * Print an error to stderr
 * @param msg	The message to print (excluding "Error: " and newline)
 * @return Returns 1 as integer for exit status code
 */
int	print_err(t_sim *sim, char *msg)
{
	if (sim)
		pthread_mutex_lock(&sim->write_lock);
	write(2, "Error: ", 7);
	write(2, msg, ph_strlen(msg));
	write(2, "\n", 1);
	if (sim)
		pthread_mutex_unlock(&sim->write_lock);
	return (1);
}

int	ph_print_fork_take(t_philo *philo)
{
	unsigned int	timestamp;
	unsigned int	elapsed_time;

	get_time_in_ms(&timestamp);
	pthread_mutex_lock(&philo->sim->status_lock);
	if (philo->sim->start == 0)
		philo->sim->start = timestamp;
	elapsed_time = timestamp - philo->sim->start;
	if (!philo->sim->stopped)
	{
		pthread_mutex_lock(&philo->sim->write_lock);
		printf("%6d %d has taken a fork\n", elapsed_time, philo->id);
		pthread_mutex_unlock(&philo->sim->write_lock);
	}
	pthread_mutex_unlock(&philo->sim->status_lock);
	return (1);
}
