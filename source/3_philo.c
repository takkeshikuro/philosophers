/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 10:54:41 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/04/28 03:13:45 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	go_eat_bis(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_mutex);
	philo->last_eat_time = get_actual_time(philo->data);
	philo->eat_cont += 1;
	pthread_mutex_unlock(&philo->data->eat_mutex);
	print_status(philo, "\033[32;1mis eating\033[0m");
	ft_sleep(philo, philo->data->t_to_eat);
}

void	go_eat(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_status(philo, "\033[0;36mhas taken a fork\033[0m");
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo, "\033[0;36mhas taken a fork\033[0m");
		go_eat_bis(philo);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_status(philo, "\033[0;36mhas taken a fork\033[0m");
		pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
		print_status(philo, "\033[0;36mhas taken a fork\033[0m");
		go_eat_bis(philo);
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	}	
}

int	check_is_finished(t_philo *philo, int ok)
{
	pthread_mutex_lock(&philo->data->finish_mutex);
	if (ok)
	{
		philo->data->finish = 1;
		pthread_mutex_unlock(&philo->data->finish_mutex);
		return (1);
	}
	if (philo->data->finish)
	{
		pthread_mutex_unlock(&philo->data->finish_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->finish_mutex);
	return (0);
}

void	*process_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(philo->data->t_to_eat);
	while (1)
	{
		go_eat(philo);
		if (check_is_finished(philo, 0))
			return (0);
		print_status(philo, "\033[0;34mis sleeping\033[0m");
		ft_sleep(philo, philo->data->t_to_sleep);
		
		print_status(philo, "\033[0;34mis thinking\033[0m");
		
		if (philo->data ->nb_of_philo % 2 != 0 &&  !check_is_finished(philo, 0))
		{
			ft_sleep(philo, (philo->data->t_to_die - (philo->data->t_to_eat + philo->data->t_to_sleep)) / 2);
		}
	}
	return (0);
}
