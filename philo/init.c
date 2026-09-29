/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:10:06 by agoudet-          #+#    #+#             */
/*   Updated: 2026/09/29 21:34:44 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Brief: Functions to initialize philo instances and simulation data

#include "philo.h"

static int	init_forks(t_data *data);

static int	init_philos(t_data *data);

void	init_data(char **argv, t_data *data)
{
	int	init_check;

	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	data->start_time = 0;
	data->run_flag = 0;
	init_check = init_forks(data);
	if (init_check != 0)
		return ;
	init_check = init_philos(data);
	if (init_check != 0)
	{
		clean_up_forks(data->forks, data->number_of_philosophers);
		return ;
	}
}

// Need to handle malloc failure cleanly
static int	init_forks(t_data *data)
{
	t_fork	*current_fork;
	size_t	total_forks;
	int		mtx_init_check;
	size_t	i;

	total_forks = (size_t)data->number_of_philosophers;
	data->forks = (t_fork *)malloc((total_forks + 1) * sizeof(t_fork));
	if (data->forks == NULL)
		return (-1);
	i = 0;
	current_fork = &(data->forks[i]);
	while (i < total_forks)
	{
		mtx_init_check = pthread_mutex_init(current_fork, NULL);
		if (mtx_init_check != 0)
		{
			clean_up_forks(data->forks, i);
			return (mtx_init_check);
		}
		i++;
		current_fork = &(data->forks[i]);
	}
	memset(current_fork, 0, sizeof(t_fork));
	return (0);
}

static int	init_philos(t_data *data)
{
	t_philo	*current_philo;
	size_t	total_philos;
	size_t	i;

	total_philos = (size_t)data->number_of_philosophers;
	data->philos = (t_philo *)malloc((total_philos + 1) * sizeof(t_philo));
	if (data->philos == NULL)
		return (-1);
	i = 1;
	current_philo = &(data->philos[i - 1]);
	while (i <= total_philos)
	{
		current_philo->id = i;
		current_philo->left_fork = i - 1;
		current_philo->right_fork = i % total_philos;
		current_philo->last_meal_time = 0;
		current_philo->meals_eaten = 0;
		i++;
		current_philo = &(data->philos[i - 1]);
	}
	memset(current_philo, 0, sizeof(t_philo));
	return (0);
}
