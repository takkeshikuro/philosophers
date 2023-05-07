/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_ending.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:33:52 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/04/26 07:06:34 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	error(char *str)
{
	printf("error : %s\n", str);
	return (1);
}

int	free_data(t_data *data)
{
	free(data->philo);
	free(data->forks);
	return (0);
}

int	free_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	free_data(data);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->eat_mutex);
	pthread_mutex_destroy(&data->finish_mutex);
	return (0);
}

void	waiting_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	free_destroy(data);
}

void	destroy(t_data *data)
{
	int	i;
	int	ok;

	i = 0;
	ok = 1;
	while (ok)
	{
		i = 0;
		while (i < data->nb_of_philo)
		{
			if (ok && check_if_dead(&data->philo[i], data))
				ok = 0;
			i++;
		}
	}
	waiting_thread(data);
}
/*
 (1)  5 800 200 200
		no one should die
 (2)  5 600 150 150
		 no one should die
(3)   4 410 200 200
 		no one should die
 (4)  100 800 200 200
 		no one should die
 (5)  105 800 200 200
 		no one should die
 (6)  200 800 200 200
 		no one should die
 (7)  1 800 200 200
 		a philo should die
 (8)  4 310 200 100
 		a philo should die
 (9)  4 200 205 200
 		a philo should die
*/