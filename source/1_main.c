/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmorikaw <tmorikaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 03:19:22 by tmorikaw          #+#    #+#             */
/*   Updated: 2023/03/28 03:05:28 by tmorikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (init_data(&data, ac, av))
		return (1);
	if (init_philos(&data))
		return (free_data(&data));
	if (init_mutex(&data))
		return (free_destroy(&data));
	if (create_philos(&data))
		return (free_destroy(&data));
	destroy(&data);
}

/* # 5 800 200 200  =  no one should die
# 5 600 150 150     =  no one should die
# 4 410 200 200     =  no one should die
# 100 800 200 200   =  no one should die
# 105 800 200 200   =  no one should die
# 200 800 200 200   =  no one should die

# 1 800 200 200     =  a philo should die
# 4 310 200 100     =  a philo should die
# 4 200 205 200     =  a philo should die
# 5 800 200 200 7   =  no one should die, simulation should stop after 7 eats
# 4 410 200 200 10  =  no one should die, simulation should stop after 10 eats
# -5 600 200 200    =  should error and not run (no crashing)
# 4 -5 200 200      =  should error and not run (no crashing)
# 4 600 -5 200      =  should error and not run (no crashing)
# 4 600 200 -5      =  should error and not run (no crashing)
# 4 600 200 200 -5  =  should error and not run (no crashing) */