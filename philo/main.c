/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 16:15:04 by agoudet-          #+#    #+#             */
/*   Updated: 2026/09/25 16:34:28 by agoudet-         ###   ########.fr       */
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
		if (*argv[i] == '-' || *argv[i] == '+')
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

static bool	non_zero_args(int argc, char **argv)
{
	int	i;
	int	arg_as_nbr;

	i = 1;
	while (i < argc)
	{
		arg_as_nbr = ft_atoi(argv[i]);
		if (arg_as_nbr == 0)
		{
			write(STDERR_FILENO, "Error: invalid argument value 0", 31);
			write(STDERR_FILENO, "\n", 1);
			return (false);
		}
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	if (!has_4_or_5_args(argc) || !no_signed_args(argc, argv)
		|| !args_are_all_digits(argc, argv) || !non_zero_args(argc, argv))
		return (1);
	return (0);
}
