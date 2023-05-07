/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 03:07:12 by keshikuro         #+#    #+#             */
/*   Updated: 2023/04/28 03:11:29 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_if_dead(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->eat_mutex);
	if ((get_actual_time(data) - philo->last_eat_time) >= data->t_to_die)
	{
		print_status(philo, "\033[31;5mdied :(\033[0m");
		check_is_finished(philo, 1);
		pthread_mutex_unlock(&data->eat_mutex);
		return (1);
	}
	else if (data->nb_of_eat > 0 && philo->eat_cont >= data->nb_of_eat)
	{
		data->nb_philo_finish += 1;
		if (data->nb_philo_finish >= data->nb_of_philo)
		{
			check_is_finished(philo, 1);
			print_status(philo, "f");
			pthread_mutex_unlock(&data->eat_mutex);
			return (1);
		}
	}
	if (philo->eat_cont >= data->nb_of_eat)
		philo->eat_cont = -100;
	pthread_mutex_unlock(&data->eat_mutex);
	return (0);
}

void	print_status(t_philo *philo, const char *str)
{
	long long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!check_is_finished(philo, 0))
	{
		time = get_actual_time(philo->data);
		printf("\033[37;3m%lld \033[35;1m%d %s\n", time, philo->id, str);
	}
	if (str[0] == 'f')
		printf("Philosophers Success\n");
	pthread_mutex_unlock(&philo->data->print_mutex);
}