/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 18:08:00 by fbes          #+#    #+#                 */
/*   Updated: 2021/11/19 19:56:45 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <pthread.h>
# define UNLIMITED_TIMES_TO_EAT -2

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	void			*ret;
}					t_philo;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_sim
{
	int				amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
	t_list			*philos;
}					t_sim;

size_t				ph_strlen(char *str);
int					ph_parse_num(char *s);
t_list				*ph_list_new(void *content);
t_list				*ph_list_last(t_list *list);
size_t				ph_list_size(t_list *list);
void				ph_list_add(t_list **list, t_list *elem);
void				ph_list_clear(t_list **list);
void				*start_routine(void *settings);

#endif
