/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoudet- <agoudet-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/23 16:15:04 by agoudet-          #+#    #+#             */
/*   Updated: 2026/10/24 18:11:53 by agoudet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	has_4_or_5_args(int argc)
{
	if (argc == 1)
	{
		print_error("No arguments given");
		return (false);
	}
	else if (argc < 5)
	{
		print_error("Too few arguments");
		return (false);
	}
	else if (argc > 6)
	{
		print_error("Too many arguments");
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
			print_error("No signed numbers accepted");
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
				print_error("Non-digit in args");
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
			print_error("invalid argument value 0");
			return (false);
		}
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			check;

	if (!has_4_or_5_args(argc) || !no_signed_args(argc, argv)
		|| !args_are_all_digits(argc, argv) || !non_zero_args(argc, argv))
		return (1);
	check = init_data(argv, &data);
	if (check != 0)
		return (1);
	check = spawn_threads(&data);
	if (check != 0)
		return (1);
	check = join_threads(&data, data.number_of_philosophers);
	if (check != 0)
	{
		printf("Error %d\n", check);
		return (1);
	}
	destroy_mutexes(&data, data.number_of_philosophers);
	free(data.philos);
	return (0);
}
