/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 17:21:44 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/22 21:12:48 by fbes          ########   odam.nl         */
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

	get_time_in_ms(&timestamp);
	pthread_mutex_lock(&philo->sim->write_lock);
	if (philo->sim->start == 0)
		philo->sim->start = timestamp;
	if (!philo->sim->stopped)
		printf("%6d %d has taken a fork\n", timestamp - philo->sim->start, philo->id);
	pthread_mutex_unlock(&philo->sim->write_lock);
	return (1);
}

/**
 * Print a philosopher for debugging
 * @param philo	The struct to print
 */
void	print_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->write_lock);
	printf("PHILOSOPHER %d\n", philo->id);
	printf("status: %d\n", philo->status);
	printf("last_ate: %d\n", philo->last_ate);
	printf("thread: %p\n", philo->thread);
	printf("returned: %p\n", philo->ret);
	printf("fork left: %p\n", philo->fork_left);
	printf("fork right: %p\n", philo->fork_right);
	printf("sim: %p\n", philo->sim);
	printf("\n");
	pthread_mutex_unlock(&philo->sim->write_lock);
}

/**
 * Set the philosopher status and print it.
 * @param[in] philo The philosopher struct
 * @param[in] status The new status of the philosopher
 * @return Returns 1 on success, 0 on error
 */
int	set_n_print_status(t_philo *philo, enum e_status status)
{
	unsigned int	timestamp;

	get_time_in_ms(&timestamp);
	pthread_mutex_lock(&philo->sim->write_lock);
	philo->status = status;
	if (philo->sim->start == 0)
		philo->sim->start = timestamp;
	timestamp = timestamp - philo->sim->start;
	if (!philo->sim->stopped)
	{
		if (status == thinking)
			printf("%6d %d is thinking\n", timestamp, philo->id);
		else if (status == eating)
		{
			pthread_mutex_lock(&philo->last_ate_lock);
			get_time_in_ms(&philo->last_ate);
			pthread_mutex_unlock(&philo->last_ate_lock);
			printf("%6d %d is eating\n", timestamp, philo->id);
		}
		else if (status == sleeping)
		{
			if (philo->sim->times_to_eat == UNLIMITED_TIMES_TO_EAT
				|| philo->times_eaten < philo->sim->times_to_eat)
				philo->times_eaten++;
			printf("%6d %d is sleeping\n", timestamp, philo->id);
		}
		else if (status == dead)
			printf("%6d %d died\n", timestamp, philo->id);
	}
	pthread_mutex_unlock(&philo->sim->write_lock);
	return (1);
}
