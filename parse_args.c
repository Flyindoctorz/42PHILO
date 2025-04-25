/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:26:03 by cgelgon           #+#    #+#             */
/*   Updated: 2025/04/25 16:52:49 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_valid_numbers(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!is_valid_number(av[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	validate_philo_args(t_data *data)
{
	if (data->nb_philo < 1 || data->nb_philo > 200)
	{
		printf("Error: number of philosophers must be between 1 and 200\n");
		return (false);
	}
	if (data->time_to_die <= 0)
	{
		printf("Error: time_to_die must be positive\n");
		return (false);
	}
	if (data->time_to_eat <= 0)
	{
		printf("Error: time_to_eat must be positive\n");
		return (false);
	}
	return (true);
}

static bool	validate_additional_args(t_data *data, int ac)
{
	if (data->time_to_sleep <= 0)
	{
		printf("Error: time_to_sleep must be positive\n");
		return (false);
	}
	if (ac == 6 && data->nb_must_eat <= 0)
	{
		printf("Error: nb_must_eat must be positive\n");
		return (false);
	}
	if (data->time_to_eat >= data->time_to_die)
	{
		printf("time_to_eat (%d) very close time_to_die (%d)\n",
			data->time_to_eat, data->time_to_die);
		// printf("philos might die before finishing eating\n");
		// return (false);
	}
	return (true);
}

bool	parse_args(t_data *data, int ac, char **av)
{
	if (!check_valid_numbers(ac, av))
		return (false);
	data->nb_philo = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	if (ac == 6)
		data->nb_must_eat = atoi(av[5]);
	else
		data->nb_must_eat = -1;
	if (!validate_philo_args(data))
		return (false);
	if (!validate_additional_args(data, ac))
		return (false);
	return (true);
}
