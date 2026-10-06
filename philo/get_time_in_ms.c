/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_in_ms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 18:58:55 by agoudet-          #+#    #+#             */
/*   Updated: 2026/10/06 15:36:12 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

ssize_t	get_time_in_ms(void)
{
	struct timeval	time;
	ssize_t			time_in_ms;
	ssize_t			time_sec_in_ms;
	ssize_t			time_usec_in_ms;
	int				gt_check;

	gt_check = gettimeofday(&time, NULL);
	if (gt_check == -1)
	{
		ft_putendl_fd("Error: gettimeofday failed", STDERR_FILENO);
		return (-1);
	}
	time_sec_in_ms = (ssize_t)(time.tv_sec * 1000);
	time_usec_in_ms = (ssize_t)(time.tv_usec / 1000);
	time_in_ms = time_sec_in_ms + time_usec_in_ms;
	return (time_in_ms);
}
