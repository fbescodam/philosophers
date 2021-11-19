/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 18:07:54 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/19 18:42:04 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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
 * Check if the options are set correctly
 * @param options	The options
 * @return			Returns 1 if set correctly, else < 0
 */
static int	options_set_correctly(t_options *options)
{
	if (options->amount < 0)
		return (-1);
	if (options->time_to_die < 0)
		return (-2);
	if (options->time_to_eat < 0)
		return (-3);
	if (options->time_to_sleep < 0)
		return (-4);
	if (options->times_to_eat != UNLIMITED_TIMES_TO_EAT
		&& options->times_to_eat < 0)
		return (-5);
	return (1);
}

static int	start(t_options *options)
{
	write(1, "Started running simulation...\n", 30);
	return (0);
}

int	main(int argc, char **argv)
{
	int			i;
	t_options	options;
	int			err;

	if (argc < 5)
		return (print_err("missing arguments"));
	else if (argc > 6)
		return (print_err("too many arguments"));
	options.amount = ph_parse_num(argv[1]);
	options.time_to_die = ph_parse_num(argv[2]);
	options.time_to_eat = ph_parse_num(argv[3]);
	options.time_to_sleep = ph_parse_num(argv[4]);
	if (argc == 6)
		options.times_to_eat = ph_parse_num(argv[5]);
	else
		options.times_to_eat = UNLIMITED_TIMES_TO_EAT;
	err = options_set_correctly(&options);
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
	else
		start(&options);
	return (0);
}
