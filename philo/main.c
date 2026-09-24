/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 16:15:04 by agoudet-          #+#    #+#             */
/*   Updated: 2026/09/24 21:13:18 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	has_4_or_5_args(int argc)
{
	if (argc == 1)
	{
		write(STDERR_FILENO, "Error: No arguments given", 25);
		write(STDERR_FILENO, "\n", 1);
		return (false);
	}
	else if (argc < 5)
	{
		write(STDERR_FILENO, "Error: Too few arguments", 24);
		write(STDERR_FILENO, "\n", 1);
		return (false);
	}
	else if (argc > 6)
	{
		write(STDERR_FILENO, "Error: Too many arguments", 25);
		write(STDERR_FILENO, "\n", 1);
		return (false);
	}
	else
		return (true);
}

static bool	no_signed_args(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (*argv[i] == '-')
		{
			write(STDERR_FILENO, "Error: No signed numbers accepted", 33);
			write(STDERR_FILENO, "\n", 1);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	args_are_all_digits(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]))
			{
				write(STDERR_FILENO, "Error: Non-digit in args", 24);
				write(STDERR_FILENO, "\n", 1);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	int	number_of_philosophers;
	int	time_to_die;

	if (!has_4_or_5_args(argc) || !no_signed_args(argc, argv)
		|| !args_are_all_digits(argc, argv))
		return (1);
	number_of_philosophers = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	if (number_of_philosophers == 0 || time_to_die == 0)
	{
		write(STDERR_FILENO, "Error: 0 philosophers or no time to die", 39);
		write(STDERR_FILENO, "\n", 1);
		return (1);
	}
	return (0);
}
