/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 16:14:01 by agoudet-          #+#    #+#             */
/*   Updated: 2026/11/02 19:25:27 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// Header inclusions

# include <sys/types.h> // for ssize_t, time_t and suseconds_t types
/*
 * NOTE: time_t and suseconds_t are data types for time in seconds and time
 * in microseconds. These are the data types for the corresponding members
 * of timeval, a struct the gettimeofday() function (more below) needs a
 * pointer to.
 *
 * Additionally, usleep requires an argument of type time_t.
 */
# include <stdbool.h> // for more explicit true/false values where required
# include <unistd.h> // for write
# include <stdio.h> // for printf
# include <string.h> // for memset
# include <stdlib.h> // for malloc and free
# include <limits.h> // for INT_MAX
# include <sys/time.h> // for timeval variables, gettimeofday and usleep
# include <pthread.h> // for multithreading (pthread and mutex management)

// Typedefs and structure definitions

typedef pthread_mutex_t	t_fork; // Alias for mutex-represented forks
typedef ssize_t	t_time_msec;	// Alias for time values in miliseconds

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	id;
	unsigned int	left_fork;
	unsigned int	right_fork;
	unsigned int	meals_eaten;
	t_time_msec		last_meal_time;
}					t_philo;

typedef struct s_data
{
	unsigned int	number_of_philosophers;
	t_time_msec		time_to_die;
	t_time_msec		time_to_eat;
	t_time_msec		time_to_sleep;
	unsigned int	number_of_times_each_philosopher_must_eat;
	t_time_msec		start;
	bool			running;
	t_fork			*forks;
	t_philo			*philos;
	size_t			philo_idx;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	state_lock;
}					t_data;

// Helper functions
size_t		ft_strlen(const char *s);
int			ft_isdigit(int c);
void		print_error(char *msg);
int			ft_atoi(const char *nptr);
int			ft_usleep(size_t ms);
int			init_data(char **argv, t_data *data);
t_time_msec	get_time_in_ms(void);
void		destroy_mutexes(t_data *data, size_t allocd);
int			spawn_threads(t_data *data);
int			join_threads(t_data *data, size_t running_threads);
void		*philo_routine(void *arg);

#endif
