/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:22:56 by agoudet-          #+#    #+#             */
/*   Updated: 2026/09/24 21:12:47 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	skip_leading_whitespace(const char *str);

static int		check_overflow(int result, int dig);

int	ft_atoi(const char *nptr)
{
	size_t		i;
	int			result;
	int			digit;

	if (nptr == NULL)
		return (0);
	result = 0;
	i = skip_leading_whitespace(nptr);
	while (ft_isdigit(nptr[i]))
	{
		digit = nptr[i] - '0';
		if (check_overflow(result, digit))
			return (0);
		result = result * 10 + digit;
		i++;
	}
	if (nptr[i] != '\0')
		return (0);
	else
		return (result);
}

static size_t	skip_leading_whitespace(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r')
		i++;
	return (i);
}

static int	check_overflow(int result, int dig)
{
	if (result > INT_MAX / 10)
		return (1);
	else if (result == INT_MAX / 10 && dig > INT_MAX % 10)
		return (1);
	else
		return (0);
}
