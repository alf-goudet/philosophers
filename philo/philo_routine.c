/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 19:19:14 by agoudet-          #+#    #+#             */
/*   Updated: 2026/11/12 21:39:22 by agoudet-         ###   ########.fr       */
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
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

// Asynchronous fork acquisition logic:
// -----------------------------------
// For philosophers with even-numbered IDs, a short pause of 10 ms is enforced
// so that odd-numbered philosophers start taking forks first, preventing
// deadlocks due to circular wait.
static void	assign_forks(t_philo *philo)
{
	const bool	id_is_even = philo->id % 2 == 0;

	if (id_is_even)
		ft_usleep(10);
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	t_time_msec	time_to_eat;
	t_time_msec	time_to_sleep;

	philo = (t_philo *)arg;
	time_to_eat = philo->data->time_to_eat;
	time_to_sleep = philo->data->time_to_sleep;
	while (1)
	{
		assign_forks(philo);
		philo->last_meal_time = get_time_in_ms();
		print_status(philo, "is eating");
		ft_usleep(time_to_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_status(philo, "is sleeping");
		ft_usleep(time_to_sleep);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
