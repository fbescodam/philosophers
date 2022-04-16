/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 18:08:00 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/16 03:32:03 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <pthread.h>

enum e_status{dead, thinking, eating, sleeping};

# define UNLIMITED_TIMES_TO_EAT -2
# define FORK_FREE 0
# define FORK_TAKEN !FORK_FREE
# define TAKE_FORK FORK_FREE
# define DROP_FORK FORK_TAKEN

typedef struct timeval	t_timeval;

typedef struct s_fork
{
	int				id;
	int				status;
	pthread_mutex_t	lock;
}					t_fork;

typedef struct s_philo
{
	int				id;
	enum e_status	status;
	unsigned int	last_ate;
	pthread_mutex_t	last_ate_lock;
	int				times_eaten;
	pthread_t		thread;
	void			*ret;
	t_fork			*fork_left;
	t_fork			*fork_right;
	struct s_sim	*sim;
}					t_philo;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_sim
{
	char			stopped;
	int				amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
	pthread_mutex_t	write_lock;
	unsigned int	start;
	t_list			*philos;
	t_list			*forks;
	pthread_t		monitor;
}					t_sim;

// helper functions

int					ph_sleep(unsigned int time_ms);
size_t				ph_strlen(char *str);
int					ph_parse_num(char *s);
t_list				*ph_list_new(void *content);
t_list				*ph_list_last(t_list *list);
t_list				*ph_list_get(t_list *list, size_t i);
size_t				ph_list_size(t_list *list);
void				ph_list_add(t_list **list, t_list *elem);
void				ph_list_clear(t_list **list);
int					get_time_in_ms(unsigned int *time_ms);

// printer functions

int					print_err(char *msg);
int					set_n_print_status(t_philo *philo, enum e_status status);
void				print_philo(t_philo *philo);
int					ph_print_fork_take(t_philo *philo);

// monitor functions

void				*start_monitor(void *sim_in_the_void);


// philosopher functions

void				*start_routine(void *philo_in_the_void);
int					get_them_forks(t_philo *philo);
int					drop_them_forks(t_philo *philo);

#endif
