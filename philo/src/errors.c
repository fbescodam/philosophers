/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/23 17:22:58 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/23 17:30:37 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_handler_sim_set_correctly(int err)
{
	if (err == -1)
		return (print_err(NULL, "invalid number of philosophers set"));
	else if (err == -2)
		return (print_err(NULL, "invalid time to die set"));
	else if (err == -3)
		return (print_err(NULL, "invalid time to eat set"));
	else if (err == -4)
		return (print_err(NULL, "invalid time to sleep set"));
	else if (err == -5)
		return (print_err(NULL, "invalid times to eat per philosopher set"));
	return (print_err(NULL, "unknown error"));
}

int	err_handler_start_sim(int err, t_sim *sim)
{
	if (err == -1 || err == -2 || err == -5 || err == -6)
		print_err(NULL, "memory allocation failure");
	else if (err == -3)
		print_err(NULL, "thread creation failure");
	else if (err == -4)
		print_err(NULL, "thread join failure");
	else if (err == -7)
		print_err(NULL, "mutex initializion failure in fork");
	else if (err == -8)
		print_err(NULL, "unable to fetch the current time");
	else
		print_err(NULL, "an unknown error occurred during simulation");
	destroyer(sim);
	return (1);
}
