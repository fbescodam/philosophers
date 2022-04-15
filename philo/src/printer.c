/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   printer.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 17:21:44 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/15 19:06:32 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

/**
 * Print an error to stderr
 * @param msg	The message to print (excluding "Error: " and newline)
 * @return Returns 1 as integer for exit status code
 */
int	print_err(char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, ph_strlen(msg));
	write(2, "\n", 1);
	return (1);
}

int	ph_print_fork_take(t_philo *philo)
{
	unsigned int	timestamp;

	if (!get_time_in_ms(&timestamp))
		return (0);
	pthread_mutex_lock(&philo->sim->write_lock);
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
 */
int	set_n_print_status(t_philo *philo, int status)
{
	int				ret;
	unsigned int	timestamp;

	if (!get_time_in_ms(&timestamp))
		return (0);
	timestamp = timestamp - philo->sim->start;
	philo->status = status;
	pthread_mutex_lock(&philo->sim->write_lock);
	if (status == STATUS_THINKING)
		printf("%6d %d is thinking\n", timestamp, philo->id);
	else if (status == STATUS_EATING)
		printf("%6d %d is eating\n", timestamp, philo->id);
	else if (status == STATUS_SLEEPING)
		printf("%6d %d is sleeping\n", timestamp, philo->id);
	else if (status == STATUS_DEAD)
		printf("%6d %d died\n", timestamp, philo->id);
	pthread_mutex_unlock(&philo->sim->write_lock);
	return (1);
}
