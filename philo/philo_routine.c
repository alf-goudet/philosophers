/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 19:19:14 by agoudet-          #+#    #+#             */
/*   Updated: 2026/11/20 14:08:40 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	simulation_is_running(t_data *data)
{
	if (data->running == false)
		return (false);
	return (true);
}

static void	take_forks(t_philo *philo)
{
	const bool	id_is_even = philo->id % 2 == 0;

	if (id_is_even)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else		
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
}
// NOTE on take_forks() above
//
// Philosophers take forks through an asymmetrical grab logic:
// 1. Even-numbered philosophers (2,4,6...) take their right fork first.
// 2. The rest (i.e. odd-numbered; 1,3,5...) take their left fork first.
//
// This strategy prevents a deadlock by breaking the circular wait condition.

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	t_time_msec	time_to_eat;
	t_time_msec	time_to_sleep;

	philo = (t_philo *)arg;
	time_to_eat = philo->data->time_to_eat;
	time_to_sleep = philo->data->time_to_sleep;
	while (simulation_is_running(philo->data))
	{
		take_forks(philo);
		philo->last_meal_time = get_time_in_ms();
		print_status(philo, "is eating");
		ft_usleep(time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		philo->meals_eaten++;
		print_status(philo, "is sleeping");
		ft_usleep(time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}

// Routine version for case of only 1 philosopher
void	*one_philo_routine(void *arg)
{
	t_data		*data;
	t_philo		*philo;
	t_time_msec	current;

	data = (t_data *)arg;
	philo = &data->philos[0];
	current = 0;
	pthread_mutex_lock(philo->left_fork);
	printf("%zd %d has taken a fork\n", current, philo->id);
	ft_usleep(data->time_to_die);
	current = get_time_in_ms() - data->start;
	printf("%zd %d died\n", current, philo->id);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}
