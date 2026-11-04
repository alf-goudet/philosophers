/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_in_ms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 18:58:55 by agoudet-          #+#    #+#             */
/*   Updated: 2026/10/27 21:27:24 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time_msec	get_time_in_ms(void)
{
	struct timeval	time;
	t_time_msec		time_in_ms;
	t_time_msec		time_sec_in_ms;
	t_time_msec		time_usec_in_ms;
	int				gt_check;

	gt_check = gettimeofday(&time, NULL);
	if (gt_check == -1)
	{
		print_error("gettimeofday failed");
		return (-1);
	}
	time_sec_in_ms = (t_time_msec)(time.tv_sec * 1000);
	time_usec_in_ms = (t_time_msec)(time.tv_usec / 1000);
	time_in_ms = time_sec_in_ms + time_usec_in_ms;
	return (time_in_ms);
}
