/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 18:07:54 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/19 22:24:49 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "philo.h"

/**
 * Print an error to stderr
 * @param msg	The message to print (excluding "Error: " and newline)
 */
static int	print_err(char *msg)
{
	write(2, "Error: ", 7);
	write(2, msg, ph_strlen(msg));
	write(2, "\n", 1);
	return (1);
}

/**
 * Check if the sim are set correctly
 * @param sim	The sim
 * @return			Returns 1 if set correctly, else < 0
 */
static int	sim_set_correctly(t_sim *sim)
{
	if (sim->amount < 0)
		return (-1);
	if (sim->time_to_die < 0)
		return (-2);
	if (sim->time_to_eat < 0)
		return (-3);
	if (sim->time_to_sleep < 0)
		return (-4);
	if (sim->times_to_eat != UNLIMITED_TIMES_TO_EAT
		&& sim->times_to_eat < 0)
		return (-5);
	return (1);
}

static int	start_sim(t_sim *sim)
{
	int			i;
	t_fork		*fork;
	t_philo		*philo;
	t_list		*elem_fork;
	t_list		*elem_philo;

	write(1, "Initializing simulation...\n", 27);
	sim->philos = NULL;
	i = 0;
	while (i < sim->amount)
	{
		fork = (t_fork *)malloc(sizeof(t_fork));
		if (!fork)
			return (-5);
		fork->id = i + 1;
		fork->status = FORK_FREE;
		elem_fork = ph_list_new((void *)fork);
		if (!elem_fork)
			return (-6);
		ph_list_add(&sim->forks, elem_fork);
		i++;
	}
	elem_fork = sim->forks;
	i = 0;
	while (i < sim->amount)
	{
		philo = (t_philo *)malloc(sizeof(t_philo));
		if (!philo)
			return (-1);
		philo->id = i + 1;
		philo->sim = sim;
		philo->fork_left = (t_fork *)elem_fork->content;
		elem_fork = elem_fork->next;
		if (!elem_fork)
			elem_fork = sim->forks;
		philo->fork_right = (t_fork *)elem_fork->content;
		elem_philo = ph_list_new((void *)philo);
		if (!elem_philo)
			return (-2);
		ph_list_add(&sim->philos, elem_philo);
		if (pthread_create(&philo->thread, NULL, &start_routine, philo))
			return (-3);
		if (pthread_join(philo->thread, &philo->ret))
			return (-4);
		i++;
	}
	write(1, "Started running simulation...\n", 30);
	return (0);
}

int	main(int argc, char **argv)
{
	int			i;
	t_sim		sim;
	int			err;

	if (argc < 5)
		return (print_err("missing arguments"));
	else if (argc > 6)
		return (print_err("too many arguments"));
	sim.amount = ph_parse_num(argv[1]);
	sim.time_to_die = ph_parse_num(argv[2]);
	sim.time_to_eat = ph_parse_num(argv[3]);
	sim.time_to_sleep = ph_parse_num(argv[4]);
	if (argc == 6)
		sim.times_to_eat = ph_parse_num(argv[5]);
	else
		sim.times_to_eat = UNLIMITED_TIMES_TO_EAT;
	err = sim_set_correctly(&sim);
	if (err == -1)
		return (print_err("invalid number of philosophers set"));
	else if (err == -2)
		return (print_err("invalid time to die set"));
	else if (err == -3)
		return (print_err("invalid time to eat set"));
	else if (err == -4)
		return (print_err("invalid time to sleep set"));
	else if (err == -5)
		return (print_err("invalid times to eat per philosopher set"));
	if (start_sim(&sim) < 0)
	{
		system("leaks philo");
		return (print_err("an error occurred during simulation"));
	}
	system("leaks philo");
	return (0);
}
