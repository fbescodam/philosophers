/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/04 17:20:25 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/15 18:51:34 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

int	change_right_fork(t_philo *philo, int new_status)
{
	int		ret;

	pthread_mutex_lock(&philo->fork_right->lock);
	if (philo->fork_right->status == new_status)
	{
		philo->fork_right->status = !new_status;
		ret = 0;
	}
	else
		ret = 1;
	pthread_mutex_unlock(&philo->fork_right->lock);
	if (ret == 0 && new_status == TAKE_FORK)
		if (!ph_print_fork_take(philo))
			return (-1);
	return (ret);
}

int	change_left_fork(t_philo *philo, int new_status)
{
	int		ret;

	pthread_mutex_lock(&philo->fork_left->lock);
	if (philo->fork_left->status == new_status)
	{
		philo->fork_left->status = !new_status;
		ret = 0;
	}
	else
		ret = 1;
	pthread_mutex_unlock(&philo->fork_left->lock);
	if (ret == 0 && new_status == TAKE_FORK)
		if (!ph_print_fork_take(philo))
			return (-1);
	return (ret);
}
