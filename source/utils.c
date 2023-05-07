/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keshikuro <keshikuro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 19:53:20 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/04/28 03:11:46 by keshikuro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	long long	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}

void	ft_sleep(t_philo *philo, long long ms)
{
	long long	t;

	t = get_time();
	while (!check_is_finished(philo, 0) && (get_time() - t) < ms)
		usleep(500);
}

long long	get_time(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

long long	get_actual_time(t_data *data)
{
	struct timeval	timeval;
	long long		result;

	gettimeofday(&timeval, NULL);
	result = (timeval.tv_sec * 1000) + (timeval.tv_usec / 1000);
	return (result - data->start_time);
}

int	check_num(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
