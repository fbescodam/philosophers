/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 17:20:25 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/22 19:52:50 by fbes          ########   odam.nl         */
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
	if (pthread_mutex_lock(&philo->fork_left->lock) != 0)
		return (0);
	ph_print_fork_take(philo, philo->fork_left);
	// printf("philo %d wants to take fork %d\n", philo->id, philo->fork_right->id);
	if (pthread_mutex_lock(&philo->fork_right->lock) != 0)
		return (0);
	ph_print_fork_take(philo, philo->fork_right);
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
	if (pthread_mutex_unlock(&philo->fork_right->lock) != 0)
		return (0);
	// printf("philo %d dropped fork %d\n", philo->id, philo->fork_left->id);
	if (pthread_mutex_unlock(&philo->fork_left->lock) != 0)
		return (0);
	return (1);
}
