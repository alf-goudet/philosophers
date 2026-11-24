/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/16 20:40:14 by agoudet-          #+#    #+#             */
/*   Updated: 2026/11/24 20:11:01 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	monitor_death(t_data *data)
{
	size_t			i;
	t_philo			*philos;
	t_time_msec		time_since_last_meal;

	philos = data->philos;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		usleep(500);
		pthread_mutex_lock(&data->state_lock);
		time_since_last_meal = get_time_in_ms() - philos[i].last_meal_time;
		pthread_mutex_unlock(&data->state_lock);
		if (time_since_last_meal >= data->time_to_die)
		{
			print_status(&philos[i], "died");
			pthread_mutex_lock(&data->state_lock);
			data->running = false;
			pthread_mutex_unlock(&data->state_lock);
			break ;
		}
		i++;
	}
}

static void	monitor_meals(t_data *data)
{
	size_t			i;
	t_philo			*philos;
	unsigned int	meals_target;

	meals_target = data->number_of_times_each_philosopher_must_eat;
	if (meals_target == 0)
		return ;
	philos = data->philos;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		usleep(500);
		pthread_mutex_lock(&data->state_lock);
		if (philos[i].meals_eaten < meals_target)
		{
			pthread_mutex_unlock(&data->state_lock);
			return ;
		}
		pthread_mutex_unlock(&data->state_lock);
		i++;
	}
	pthread_mutex_lock(&data->state_lock);
	data->running = false;
	pthread_mutex_unlock(&data->state_lock);
}

void	*philo_monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (data->running)
	{
		monitor_death(data);
		monitor_meals(data);
	}
	return (NULL);
}
