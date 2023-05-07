/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_init_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:02:15 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/04/26 08:06:33 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	create_philos(t_data *data)
{
	int	i;

	i = 0;
	if (data->nb_of_philo == 1)
	{
		print_status(data->philo, "\033[0;36mis taking left fork\033[0m");
		ft_sleep(data->philo, data->t_to_die);
		print_status(data->philo, "\033[31;5mdied :(\033[0m");
		return (1);
	}
	while (i < data->nb_of_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, \
				process_start, &(data->philo[i])))
			return (error("pthread_create.\n"));
		i++;
	}
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (error("mutex_init : forks.\n"));
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (error("mutex_init : print.\n"));
	if (pthread_mutex_init(&data->eat_mutex, NULL))
		return (error("mutex_init : eat.\n"));
	if (pthread_mutex_init(&data->finish_mutex, NULL))
		return (error("mutex_init : finish.\n"));
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * data->nb_of_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philo);
	if (!data->philo || !data->forks)
		return (error("malloc failed.\n"));
	data->start_time = get_time();
	while (i < data->nb_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = i;
		data->philo[i].right_fork = (i + 1) % data->nb_of_philo;
		data->philo[i].eat_cont = 0;
		data->philo[i].last_eat_time = data->start_time;
		data->philo[i].data = data;
		i++;
	}
	return (0);
}

int	check_if_null(t_data *data)
{
	if (data->nb_of_philo == 0)
		return (1);
	if (data->t_to_die == 0)
		return (1);
	if (data->t_to_eat == 0)
		return (1);
	if (data->t_to_sleep == 0)
		return (1);
	return (0);
}

int	init_data(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (error("wrong number of args"));
	if (!check_num(av))
	{
		data->nb_of_philo = ft_atoi(av[1]);
		data->t_to_die = ft_atoi(av[2]);
		data->t_to_eat = ft_atoi(av[3]);
		data->t_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
		{
			if (ft_atoi(av[5]) == 0)
				return (error("nb of meals can't be null"));
			data->nb_of_eat = ft_atoi(av[5]);
			data->nb_philo_finish = 0;
		}
		else
			data->nb_of_eat = -1;
		data->finish = 0;
	}
	else
		return (error("wrong input"));
	if (check_if_null(data))
		return (error("wrong input (input can't be null)"));
	return (0);
}
