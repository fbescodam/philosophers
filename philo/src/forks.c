/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 17:20:25 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/16 01:33:00 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "philo.h"

/**
 * Get the forks left and right of a philosopher
 * @param[in] philo The philosopher to fetch the forks for
 * @return Returns 1 on success, 0 on error
 */
int	get_them_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		if (pthread_mutex_lock(&philo->fork_right->lock) != 0)
			return (0);
		ph_print_fork_take(philo);
		if (pthread_mutex_lock(&philo->fork_left->lock) != 0)
			return (0);
		ph_print_fork_take(philo);
	}
	else
	{
		if (pthread_mutex_lock(&philo->fork_left->lock) != 0)
			return (0);
		ph_print_fork_take(philo);
		if (pthread_mutex_lock(&philo->fork_right->lock) != 0)
			return (0);
		ph_print_fork_take(philo);
	}
	return (1);
}

/**
 * Drop the forks left and right of a philosopher
 * @param[in] philo The philosopher to drop the forks from
 * @return Returns 1 on success, 0 on error
 */
int	drop_them_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		usleep(100000);
		if (pthread_mutex_unlock(&philo->fork_right->lock) != 0)
			return (0);
		if (pthread_mutex_unlock(&philo->fork_left->lock) != 0)
			return (0);
	}
	else
	{
		if (pthread_mutex_unlock(&philo->fork_left->lock) != 0)
			return (0);
		if (pthread_mutex_unlock(&philo->fork_right->lock) != 0)
			return (0);
	}
	return (1);
}
