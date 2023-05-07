/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 03:18:46 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/04/26 04:21:01 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				eat_cont;
	long long		last_eat_time;
	struct s_data	*data;
	pthread_t		thread;
}					t_philo;

typedef struct s_data
{
	int				nb_of_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nb_of_eat;
	int				nb_philo_finish;
	int				finish;
	long long		start_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	finish_mutex;
}					t_data;

// init_all.c
int					create_philos(t_data *data);
int					init_mutex(t_data *data);
int					init_philos(t_data *data);
int					init_data(t_data *data, int ac, char **av);
int					check_if_null(t_data *data);


// philo.c
int					check_if_dead(t_philo *philo, t_data *data);
void				print_status(t_philo *philo, const char *str);
void				go_eat(t_philo *philo);
int					check_is_finished(t_philo *philo, int ok);
void				*process_start(void *arg);

// ending.c
int					error(char *str);
int					free_data(t_data *data);
int					free_destroy(t_data *data);
void				waiting_thread(t_data *data);
void				destroy(t_data *data);

// utils.c
int					ft_atoi(const char *str);
void				ft_sleep(t_philo *philo, long long ms);
long long			get_time(void);
int					check_num(char **tab);
long long			get_actual_time(t_data *data);

#endif