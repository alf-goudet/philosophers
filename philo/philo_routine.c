/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 19:19:14 by agoudet-          #+#    #+#             */
/*   Updated: 2026/11/10 20:20:25 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	return (NULL);
}

static void	eat(t_philo *philo, t_time_msec *current)
{
	t_data		*data;
	t_time_msec	start;
	t_time_msec	time_to_eat;
	
	data = philo->data;
	start = data->start;
	time_to_eat = data->time_to_eat;
	pthread_mutex_lock(philo->left_fork);
	*current = get_time_in_ms();
	printf("%zd %d has taken a fork\n", *current - start, philo->id);
	pthread_mutex_lock(philo->right_fork);
	*current = get_time_in_ms();
	printf("%zd %d has taken a fork\n", *current - start, philo->id);
	philo->last_meal_time = get_time_in_ms();
	*current = philo->last_meal_time;
	printf("%zd %d is eating\n", *current - start, philo->id);
	ft_usleep(time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	t_time_msec	current;
	t_time_msec	start;

	philo = (t_philo *)arg;
	start = philo->data->start;
	while (1)
	{
		eat(philo, &current);
		current = get_time_in_ms();
		printf("%zd %d is sleeping\n", current - start, philo->id);
		ft_usleep(philo->data->time_to_sleep);
		current = get_time_in_ms();
		printf("%zd %d is thinking\n", current - start, philo->id);
	}
	return (NULL);
}
