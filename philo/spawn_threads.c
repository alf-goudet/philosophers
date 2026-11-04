/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 19:26:27 by agoudet-          #+#    #+#             */
/*   Updated: 2026/11/04 21:11:50 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	spawn_threads(t_data *data)
{
	size_t		*i_ptr;
	size_t		i;
	size_t		total_philos;
	pthread_t	*curr_thread;
	int			check;

	total_philos = data->number_of_philosophers;
	i_ptr = &data->philo_idx;
	i = 0;
	while (i < total_philos)
	{
		*i_ptr = i;
		curr_thread = &(data->philos[i].thread);
		check = pthread_create(curr_thread, NULL, &philo_routine, data);
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
	t_philo		*curr_philo;
	int			check;

	i = 0;
	while (i < running_threads)
	{
		curr_philo = &(data->philos[i]);
		check = pthread_join(curr_philo->thread, NULL);
		if (check != 0)
		{
			print_error("Couldn't join a thread");
			return (check);
		}
		i++;
	}
	return (0);
}
