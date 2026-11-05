/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 19:19:14 by agoudet-          #+#    #+#             */
/*   Updated: 2026/11/05 20:41:12 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_data		*data;
	t_philo		*curr_philo;
	t_time_msec	current_time;

	data = (t_data *)arg;
	curr_philo = &data->philos[data->philo_idx];
	data->start = get_time_in_ms();
	current_time = 0;
	if (data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(data->forks + curr_philo->left_fork);
		printf("%zd %d has taken a fork\n", current_time, curr_philo->id);
		ft_usleep(data->time_to_die);
		current_time = get_time_in_ms() - data->start;
		printf("%zd %d died\n", current_time, curr_philo->id);
		ft_usleep(10);
		return (NULL);
	}
	printf("Hello from thread %u\n", curr_philo->id);
	return (NULL);
}
