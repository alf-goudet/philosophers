/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 19:59:27 by agoudet-          #+#    #+#             */
/*   Updated: 2026/09/29 21:39:33 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up_forks(t_fork *forks, size_t allocd)
{
	size_t	i;

	i = 0;
	while (i < allocd)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
}
