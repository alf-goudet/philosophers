/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 16:14:01 by agoudet-          #+#    #+#             */
/*   Updated: 2026/10/06 14:52:10 by agoudet-         ###   ########.fr       */
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

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		thread;
	unsigned int	left_fork;
	unsigned int	right_fork;
	unsigned int	last_meal_time;
	unsigned int	meals_eaten;
}					t_philo;

typedef struct s_data
{
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_times_each_philosopher_must_eat;
	unsigned int	start_time;
	unsigned int	run_flag;
	t_fork			*forks;
	t_philo			*philos;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*state_lock;
}					t_data;

// Helper functions
size_t		ft_strlen(const char *s);
int			ft_isdigit(int c);
void		ft_putendl_fd(char *s, int fd);
int			ft_atoi(const char *nptr);
int			ft_usleep(size_t ms);
int			init_data(char **argv, t_data *data);
ssize_t		get_time_in_ms(void);
void		clean_up_forks(t_fork *forks, size_t allocd);

#endif
