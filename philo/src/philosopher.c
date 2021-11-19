/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 19:19:19 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/19 22:30:50 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "philo.h"

/**
 * Print a philosopher for debugging
 * @param philo	The struct to print
 */
static void	print_philo(t_philo *philo)
{
	printf("PHILOSOPHER %d\n", philo->id);
	printf("status: %d\n", philo->status);
	printf("last_ate: %d\n", philo->last_ate.tv_usec);
	printf("thread: %p\n", philo->thread);
	printf("returned: %p\n", philo->ret);
	printf("fork left: %p\n", philo->fork_left);
	printf("fork right: %p\n", philo->fork_right);
	printf("sim: %p\n", philo->sim);
	printf("\n");
}

/**
 * Start a philosopher's routine
 * @param philo	A struct containing the philosopher's details
 * @return		Returns NULL
 */
void	*start_routine(void *philo)
{
	((t_philo *)philo)->status = STATUS_THINKING;
	gettimeofday(&((t_philo *)philo)->last_ate, NULL);
	print_philo(philo);
	return (NULL);
}
