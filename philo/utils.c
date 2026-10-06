/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 16:15:55 by agoudet-          #+#    #+#             */
/*   Updated: 2026/10/06 15:05:19 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putendl_fd(char *s, int fd)
{
	size_t	len;

	len = ft_strlen(s);
	write(fd, s, len);
	write(fd, "\n", 1);
}

int	ft_usleep(size_t ms)
{
	int					check;
	ssize_t				current_time;
	size_t				start_time;
	size_t				elapsed_time;
	const suseconds_t	half_a_ms = 500;

	current_time = get_time_in_ms();
	if (current_time == -1)
		return (-1);
	start_time = (size_t)current_time;
	elapsed_time = 0;
	while (elapsed_time < ms)
	{
		check = usleep(half_a_ms);
		if (check == -1)
		{
			ft_putendl_fd("Error: usleep failed", STDERR_FILENO);
			return (-1);
		}
		current_time = get_time_in_ms();
		if (current_time == -1)
			return (-1);
		elapsed_time = (size_t)current_time - start_time;
	}
	return (0);
}
