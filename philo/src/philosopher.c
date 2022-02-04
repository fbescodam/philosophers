/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 19:19:19 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/04 17:26:17 by fbes          ########   odam.nl         */
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
	pthread_mutex_lock(&philo->sim->write_lock);
	printf("PHILOSOPHER %d\n", philo->id);
	printf("status: %d\n", philo->status);
	printf("last_ate: %lds, %dms\n", philo->last_ate.tv_sec, philo->last_ate.tv_usec);
	printf("thread: %p\n", philo->thread);
	printf("returned: %p\n", philo->ret);
	printf("fork left: %p\n", philo->fork_left);
	printf("fork right: %p\n", philo->fork_right);
	printf("sim: %p\n", philo->sim);
	printf("\n");
	pthread_mutex_unlock(&philo->sim->write_lock);
}

static void	set_status(t_philo *philo, int status)
{
	philo->status = status;
	pthread_mutex_lock(&philo->sim->write_lock);
	if (status == STATUS_THINKING)
		printf("FUTURE_TIMESTAMP %d is thinking\n", philo->id);
	else if (status == STATUS_EATING)
		printf("FUTURE_TIMESTAMP %d is eating\n", philo->id);
	else if (status == STATUS_SLEEPING)
		printf("FUTURE_TIMESTAMP %d is sleeping", philo->id);
	else if (status == STATUS_DEAD)
		printf("FUTURE_TIMESTAMP %d died", philo->id);
	pthread_mutex_unlock(&philo->sim->write_lock);
	simulate(philo);
}

static void	try_fetch_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		if (change_right_fork(philo, TAKE_FORK) == 0)
		{
			if (change_left_fork(philo, TAKE_FORK) == 0)
			{
				set_status(philo, STATUS_EATING);
				return ;
			}
			change_right_fork(philo, DROP_FORK);
		}
	}
	else
	{
		if (change_left_fork(philo, TAKE_FORK) == 0)
		{
			if (change_right_fork(philo, TAKE_FORK) == 0)
			{
				set_status(philo, STATUS_EATING);
				return ;
			}
			change_left_fork(philo, DROP_FORK);
		}
	}
	set_status(philo, STATUS_THINKING);
}

void	decide_on_next_status(t_philo *philo)
{
	if (philo->status == STATUS_EATING)
		set_status(philo, STATUS_SLEEPING);
	else
		try_fetch_forks(philo);
}

/**
 * Start a philosopher's routine
 * @param philo	A struct containing the philosopher's details
 * @return		Returns NULL
 */
void	*start_routine(void *philo)
{
	((t_philo *)philo)->last_ate = ((t_philo *)philo)->sim->start;
	print_philo((t_philo *)philo);
	decide_on_next_status(philo);
	return (NULL);
}
