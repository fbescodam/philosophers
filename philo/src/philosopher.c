/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 19:19:19 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/16 00:10:59 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"

/**
 * Simulate one day of a philosopher's life
 * @param[in] philo The philosopher to simulate
 * @return Returns 0 on success, < 0 on error
 */
static int	simulate(t_philo *philo)
{
	if (!get_them_forks(philo))
		return (-3);
	if (!set_n_print_status(philo, eating))
		return (-1);
	if (!ph_sleep(philo->sim->time_to_eat))
		return (-2);
	if (!drop_them_forks(philo))
		return (-4);
	if (!set_n_print_status(philo, sleeping))
		return (-1);
	if (!set_n_print_status(philo, thinking))
		return (-1);
	return (0);
}

/**
 * Start a philosopher's routine
 * @param philo	A struct containing the philosopher's details
 * @return		Returns NULL
 */
void	*start_routine(void *philo_in_the_void)
{
	t_philo		*philo;
	int			ret;

	philo = (t_philo *)philo_in_the_void;
	while (!((t_philo *)philo)->sim->started)
		continue ;
	((t_philo *)philo)->last_ate = ((t_philo *)philo)->sim->start;
	while (!philo->sim->stopped)
	{
		if (simulate(philo) < 0)
			print_err("an error occurred while simulating a philosopher");
	}
	return (NULL);
}
