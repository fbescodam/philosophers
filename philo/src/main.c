/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 18:07:54 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/23 17:29:30 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

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

static int	start_sim(t_sim *sim)
{
	int			ret;

	sim->philos = NULL;
	sim->forks = NULL;
	ret = init_forks(sim);
	if (ret < 0)
		return (ret);
	ret = init_philos(sim);
	if (ret < 0)
		return (ret);
	ret = start_threads(sim);
	if (ret < 0)
		return (ret);
	return (0);
}

void	destroyer(t_sim *sim)
{
	t_list		*elem;

	if (pthread_mutex_destroy(&sim->write_lock))
		print_err(NULL, "could not destroy write_lock mutex");
	if (pthread_mutex_destroy(&sim->status_lock))
		print_err(NULL, "could not destroy status_lock mutex");
	elem = sim->forks;
	while (elem)
	{
		if (pthread_mutex_destroy(&((t_fork *)elem->content)->lock))
			print_err(NULL, "could not destroy a fork mutex");
		elem = elem->next;
	}
	elem = sim->philos;
	while (elem)
	{
		if (pthread_mutex_destroy(&((t_philo *)elem->content)->last_ate_lock))
			print_err(NULL, "could not destroy a last_ate_lock mutex");
		elem = elem->next;
	}
}

static void	setup_sim(t_sim *sim, int argc, char **argv)
{
	sim->stopped = 0;
	sim->start = 0;
	sim->amount = ph_parse_num(argv[1]);
	sim->time_to_die = ph_parse_num(argv[2]);
	sim->time_to_eat = ph_parse_num(argv[3]);
	sim->time_to_sleep = ph_parse_num(argv[4]);
	if (argc == 6)
		sim->times_to_eat = ph_parse_num(argv[5]);
	else
		sim->times_to_eat = UNLIMITED_TIMES_TO_EAT;
}

int	main(int argc, char **argv)
{
	t_sim		sim;
	int			err;

	if (argc < 5)
		return (print_err(NULL, "missing arguments"));
	else if (argc > 6)
		return (print_err(NULL, "too many arguments"));
	setup_sim(&sim, argc, argv);
	err = sim_set_correctly(&sim);
	if (err < 0)
		return (err_handler_sim_set_correctly(err));
	if (pthread_mutex_init(&sim.write_lock, NULL) != 0)
		return (print_err(NULL, "mutex initialization failure in write_lock"));
	if (pthread_mutex_init(&sim.status_lock, NULL) != 0)
	{
		if (pthread_mutex_destroy(&sim.write_lock))
			print_err(NULL, "could not destroy write_lock mutex");
		return (print_err(NULL, "mutex initialization failure in status_lock"));
	}
	err = start_sim(&sim);
	if (err < 0)
		return (err_handler_start_sim(err, &sim));
	destroyer(&sim);
	return (0);
}
