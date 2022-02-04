/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 18:07:54 by fbes          #+#    #+#                 */
/*   Updated: 2022/02/04 17:02:49 by fbes          ########   odam.nl         */
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
 * @return		Returns 1 if set correctly, else < 0
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

// TODO free memory before return
static int	start_sim(t_sim *sim)
{
	int			i;
	t_fork		*fork;
	t_philo		*philo;
	t_list		*elem_fork;
	t_list		*elem_philo;

	write(1, "Initializing simulation...\n", 27);
	sim->philos = NULL;
	sim->forks = NULL;
	i = 0;
	while (i < sim->amount)
	{
		//write(1, "Generating fork...\n", 20);
		fork = (t_fork *)malloc(sizeof(t_fork));
		if (!fork)
			return (-5);
		fork->id = i + 1;
		fork->status = FORK_FREE;
		if (pthread_mutex_init(&fork->lock, NULL) != 0)
			return (-7);
		//write(1, "Creating new list elem for fork...\n", 36);
		elem_fork = ph_list_new((void *)fork);
		if (!elem_fork)
			return (-6);
		//write(1, "Adding fork to list of forks...\n", 33);
		ph_list_add(&sim->forks, elem_fork);
		i++;
	}
	write(1, "Forks have been generated\n", 27);
	elem_fork = sim->forks;
	i = 0;
	while (i < sim->amount)
	{
		philo = (t_philo *)malloc(sizeof(t_philo));
		if (!philo)
			return (-1);
		philo->id = i + 1;
		philo->status = STATUS_THINKING;
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
		write(1, "Philosopher generated\n", 23);
		i++;
	}
	if (gettimeofday(&sim->start, NULL) != 0)
		return (-8);
	sim->running = 1;
	elem_philo = sim->philos;
	i = 0;
	while (i < sim->amount)
	{
		if (pthread_create(&philo->thread, NULL, &start_routine, philo) != 0)
			return (-3);
		if (pthread_join(philo->thread, &philo->ret) != 0)
			return (-4);
		elem_philo = elem_philo->next;
		i++;
	}
	write(1, "Started running simulation...\n", 30);
	return (0);
}

static void	destroyer(t_sim *sim)
{
	t_list		*elem_fork;

	if (pthread_mutex_destroy(&sim->write_lock) != 0)
		print_err("could not destroy a mutex");
	elem_fork = sim->forks;
	while (elem_fork)
	{
		if (pthread_mutex_destroy(&((t_fork *)elem_fork->content)->lock) != 0)
			print_err("could not destroy a mutex");
		elem_fork = elem_fork->next;
	}
	system("leaks philo");
}

// TODO: return(print_err) should probably run destroyer() first
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
	if (pthread_mutex_init(&sim.write_lock, NULL) != 0)
		return (print_err("mutex initialization failure in write_lock"));
	err = start_sim(&sim);
	if (err < 0)
	{
		if (err == -1 || err == -2 || err == -5 || err == -6)
			print_err("memory allocation failure");
		else if (err == -3)
			print_err("thread creation failure");
		else if (err == -4)
			print_err("thread join failure");
		else if (err == -7)
			print_err("mutex initializion failure in fork");
		else if (err == -8)
			print_err("unable to fetch the current time");
		else
			print_err("an unknown error occurred during simulation");
		destroyer(&sim);
	}
	destroyer(&sim);
}
