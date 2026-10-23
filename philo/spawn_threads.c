/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 19:26:27 by agoudet-          #+#    #+#             */
/*   Updated: 2026/10/23 20:01:19 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	spawn_threads(t_data *data)
{
	size_t		i;
	size_t		total_philos;
	t_philo		*curr_philo;
	pthread_t	*curr_thread;
	int			check;

	total_philos = data->number_of_philosophers;
	i = 0;
	while (i < total_philos)
	{
		curr_philo = &data->philos[i];
		curr_thread = &curr_philo->thread;
		check = pthread_create(curr_thread, NULL, &philo_routine, curr_philo);
		if (check != 0)
		{
			print_error("Couldn't create a thread");
			data->running = false;
			join_threads(data, i);
			destroy_mutexes(data, total_philos);
			return (check);
		}
		i++;
	}
	return (join_threads(data, total_philos));
}

int	join_threads(t_data *data, size_t running_threads)
{
	size_t		i;
	size_t		total_philos;
	t_philo		*philos;
	pthread_t	curr_thread;
	int			check;

	philos = data->philos;
	i = 0;
	while (i < running_threads)
	{
		curr_thread = (philos + i)->thread;
		check = pthread_join(curr_thread, NULL);
		if (check != 0)
		{
			print_error("Couldn't join a thread");
			return (check);
		}
		i++;
	}
	return (0);
}
