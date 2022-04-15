/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 19:19:19 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/15 19:05:58 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

/**
 * Try and fetch forks
 * @return Returns 1 if both were fetched, 0 if not
 */
static int	try_fetch_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		if (change_right_fork(philo, TAKE_FORK) == 0)
		{
			if (change_left_fork(philo, TAKE_FORK) == 0)
				return (1);
			change_right_fork(philo, DROP_FORK);
		}
	}
	else if (change_left_fork(philo, TAKE_FORK) == 0)
	{
		if (change_right_fork(philo, TAKE_FORK) == 0)
			return (1);
		change_left_fork(philo, DROP_FORK);
	}
	return (0);
}

int	decide_on_next_status(t_philo *philo)
{
	unsigned int	time;

	if (!get_time_in_ms(&time))
		return (-1);
	if (time - philo->last_ate > philo->sim->time_to_die)
	{
		if (!set_n_print_status(philo, STATUS_DEAD))
			return (-1);
		return (2);
	}
	if (philo->status == STATUS_EATING)
	{
		change_left_fork(philo, DROP_FORK);
		change_right_fork(philo, DROP_FORK);
		if (!set_n_print_status(philo, STATUS_SLEEPING))
			return (-1);
		return (simulate(philo));
	}
	else if (try_fetch_forks(philo))
	{
		if (!set_n_print_status(philo, STATUS_EATING))
			return (-1);
		return (simulate(philo));
	}
	else if (philo->status != STATUS_THINKING)
	{
		if (!set_n_print_status(philo, STATUS_THINKING))
			return (-1);
		return (simulate(philo));
	}
	return (0);
}

/**
 * Start a philosopher's routine
 * @param philo	A struct containing the philosopher's details
 * @return		Returns NULL
 */
void	*start_routine(void *philo)
{
	while (!((t_philo *)philo)->sim->started)
	{
		ph_sleep(philo, 5);
	}
	((t_philo *)philo)->last_ate = ((t_philo *)philo)->sim->start;
	decide_on_next_status(philo);
	return (NULL);
}
