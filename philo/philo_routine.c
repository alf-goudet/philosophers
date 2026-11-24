/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 19:19:14 by agoudet-          #+#    #+#             */
/*   Updated: 2026/11/24 20:08:09 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks_and_eat(t_philo *philo)
{
	const bool	id_is_even = philo->id % 2 == 0;
	t_time_msec	time_to_eat;

	time_to_eat = philo->data->time_to_eat;
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
	pthread_mutex_lock(&philo->data->state_lock);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->data->state_lock);
	print_status(philo, "is eating");
	ft_usleep(time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);	
}
// NOTE on taking of forks
//
// Philosophers take their forks through an asymmetrical grab logic:
// 1. Even-numbered philosophers (2,4,6...) take their right fork first.
// 2. The rest (i.e. odd-numbered; 1,3,5...) take their left fork first.
//
// This strategy prevents a deadlock by breaking the circular wait condition.

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	t_time_msec	time_to_sleep;

	philo = (t_philo *)arg;
	time_to_sleep = philo->data->time_to_sleep;
	pthread_mutex_lock(&philo->data->state_lock);
	while (philo->data->running)
	{
		pthread_mutex_unlock(&philo->data->state_lock);
		take_forks_and_eat(philo);
		pthread_mutex_lock(&philo->data->state_lock);
		philo->meals_eaten++;
		pthread_mutex_unlock(&philo->data->state_lock);
		print_status(philo, "is sleeping");
		ft_usleep(time_to_sleep);
		print_status(philo, "is thinking");
		pthread_mutex_lock(&philo->data->state_lock);
	}
	pthread_mutex_unlock(&philo->data->state_lock);
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
