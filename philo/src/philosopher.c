/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosopher.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 19:19:19 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/23 16:17:08 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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
	set_n_print_status(philo, eating);
	if (!ph_sleep(philo->sim->time_to_eat))
		return (-2);
	if (!drop_them_forks(philo))
		return (-4);
	set_n_print_status(philo, sleeping);
	if (!ph_sleep(philo->sim->time_to_sleep))
		return (-2);
	set_n_print_status(philo, thinking);
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
	int			stopped;

	philo = (t_philo *)philo_in_the_void;
	if (philo->sim->amount % 2 == 1)
		usleep(philo->id % 3 * 1000);
	else
		usleep(philo->id % 2 * 1000);
	pthread_mutex_lock(&philo->last_ate_lock);
	get_time_in_ms(&philo->last_ate);
	pthread_mutex_unlock(&philo->last_ate_lock);
	while (1)
	{
		pthread_mutex_lock(&philo->sim->status_lock);
		stopped = philo->sim->stopped;
		pthread_mutex_unlock(&philo->sim->status_lock);
		if (stopped)
			break ;
		if (simulate(philo) < 0)
			print_err(philo->sim, "an error occurred in philo simulation");
	}
	return (NULL);
}
