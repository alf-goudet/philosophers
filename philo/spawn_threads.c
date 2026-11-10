/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 19:26:27 by agoudet-          #+#    #+#             */
/*   Updated: 2026/11/10 21:43:56 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pthread_create_error(t_data *data, size_t i, size_t total_philos)
{
	print_error("Couldn't create a thread");
	data->running = false;
	join_threads(data, i);
	destroy_mutexes(data, total_philos);	
}

static void	one_philo_case(t_data *data)
{
	t_philo	*philo;

	philo = &(data->philos[0]);
	pthread_create(&(philo->thread), NULL, &one_philo_routine, data);
	pthread_join(philo->thread, NULL);
}

int	spawn_threads(t_data *data, size_t total_philos)
{
	size_t		i;
	t_philo		*curr_philo;
	pthread_t	*curr_thread;
	int			check;

	data->start = get_time_in_ms();
	if (total_philos == 1)
	{
		one_philo_case(data);
		return (0);
	}
	i = 0;
	while (i < total_philos)
	{
		curr_philo = &(data->philos[i]);
		curr_thread = &(curr_philo->thread);
		check = pthread_create(curr_thread, NULL, &philo_routine, curr_philo);
		if (check != 0)
			return (pthread_create_error(data, i, total_philos), check);
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
