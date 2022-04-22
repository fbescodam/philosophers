/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   useful.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 18:16:59 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/22 21:14:28 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philo.h"

/**
 * Get the length of a string
 * @param str	The string to get the length of
 * @return		The length of said string
 */
size_t	ph_strlen(char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/**
 * Parse a number. Only positive numbers are supported. The full string should
 * consist of numeric characters.
 * @param s	The string to parse the number from
 * @return	The parsed number, or -1 on error
 */
int	ph_parse_num(char *s)
{
	unsigned int	num;
	size_t			i;

	i = 0;
	num = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			num = num * 10 + ((unsigned int)s[i] - '0');
		else
			return (-1);
		i++;
	}
	return (num);
}

/**
 * C's gettimeofday wrapper
 * @param[in] time_ms A pointer to the unsigned int to write the current timestamp to
 * @return Returns 1
 */
int	get_time_in_ms(unsigned int *time_ms)
{
	t_timeval	curtime;

	gettimeofday(&curtime, NULL);
	*time_ms = curtime.tv_sec * 1000 + curtime.tv_usec / 1000;
	return (1);
}
