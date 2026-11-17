/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 20:40:14 by agoudet-          #+#    #+#             */
/*   Updated: 2026/11/17 21:09:24 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_monitor(void *arg)
{
	t_data			*data;
	t_time_msec		since_last_meal;
	t_philo			*philos;
	size_t			i;

	data = (t_data *)arg;
	philos = data->philos;
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			usleep(1000);
			since_last_meal = get_time_in_ms() - philos[i].last_meal_time;
			if (since_last_meal >= data->time_to_die)
			{
				print_status(&philos[i], "died");
				data->running = false;
				break ;
			}
			i++;
		}
	}
	return (NULL);
}
