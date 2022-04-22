/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 17:20:25 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/22 21:06:55 by fbes          ########   odam.nl         */
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
	// printf("philo %d wants to take fork %d\n", philo->id, philo->fork_left->id);
	pthread_mutex_lock(&philo->fork_left->lock);
	ph_print_fork_take(philo);
	// printf("philo %d wants to take fork %d\n", philo->id, philo->fork_right->id);
	pthread_mutex_lock(&philo->fork_right->lock);
	ph_print_fork_take(philo);
	return (1);
}

/**
 * Drop the forks left and right of a philosopher
 * @param[in] philo The philosopher to drop the forks from
 * @return Returns 1 on success, 0 on error
 */
int	drop_them_forks(t_philo *philo)
{
	// printf("philo %d dropped fork %d\n", philo->id, philo->fork_right->id);
	pthread_mutex_unlock(&philo->fork_right->lock);
	// printf("philo %d dropped fork %d\n", philo->id, philo->fork_left->id);
	pthread_mutex_unlock(&philo->fork_left->lock);
	return (1);
}
