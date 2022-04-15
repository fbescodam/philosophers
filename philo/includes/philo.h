/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/19 18:08:00 by fbes          #+#    #+#                 */
/*   Updated: 2022/04/15 18:50:09 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <stddef.h>
# include <pthread.h>

# define UNLIMITED_TIMES_TO_EAT -2
# define STATUS_DEAD 0
# define STATUS_THINKING 1
# define STATUS_EATING 2
# define STATUS_SLEEPING 3
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
	int				status;
	unsigned int	last_ate;
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
	char			started;
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
}					t_sim;

int					ph_sleep(t_philo *philo, unsigned int time_ms);
size_t				ph_strlen(char *str);
int					ph_parse_num(char *s);
t_list				*ph_list_new(void *content);
t_list				*ph_list_last(t_list *list);
t_list				*ph_list_get(t_list *list, size_t i);
size_t				ph_list_size(t_list *list);
void				ph_list_add(t_list **list, t_list *elem);
void				ph_list_clear(t_list **list);
void				*start_routine(void *settings);
int					simulate(t_philo *philo);
int					change_right_fork(t_philo *philo, int new_status);
int					change_left_fork(t_philo *philo, int new_status);
int					decide_on_next_status(t_philo *philo);
int					get_time_in_ms(unsigned int *time_ms);

int					print_err(char *msg);
int					set_n_print_status(t_philo *philo, int status);
void				print_philo(t_philo *philo);
int					ph_print_fork_take(t_philo *philo);

#endif
