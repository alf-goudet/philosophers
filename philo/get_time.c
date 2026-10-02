/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 18:58:55 by agoudet-          #+#    #+#             */
/*   Updated: 2026/10/02 20:15:18 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_ms(void)
{
	struct timeval	time;
	long			time_in_ms;
	int				gt_check;

	gt_check = gettimeofday(&time, NULL);
	if (gt_check == -1)
	{
		ft_putendl_fd("Error: gettimeofday failed", STDERR_FILENO);
		return (-1);
	}
	printf("Time retrieved by gettimeofday: %ld\n", time.tv_sec);
	return ();
}
