/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 16:14:01 by agoudet-          #+#    #+#             */
/*   Updated: 2026/09/24 21:12:59 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// Header inclusions
# include <unistd.h> // for write
# include <stdio.h> // for printf
# include <stdbool.h> // for more explicit true/false values where required
# include <limits.h> // for INT_MAX

// Typedefs and structure definitions

// Helper functions
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);

#endif
