/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_ending.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 17:33:52 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/05/07 19:21:37 by keshikuro        ###   ########.fr       */
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
