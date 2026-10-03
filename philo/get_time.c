/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 18:58:55 by agoudet-          #+#    #+#             */
/*   Updated: 2026/10/03 19:12:05 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_in_ms(void)
{
	struct timeval	time;
	long long		time_in_ms;
	int				gt_check;

	gt_check = gettimeofday(&time, NULL);
	if (gt_check == -1)
	{
		ft_putendl_fd("Error: gettimeofday failed", STDERR_FILENO);
		return (-1);
	}
	time_in_ms = (long long)((time.tv_sec * 1000) + (time.tv_usec / 1000));
	printf("Time in miliseconds: %lld\n", time_in_ms);
	return (time_in_ms);
}
