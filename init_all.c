/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:51:08 by cgelgon           #+#    #+#             */
/*   Updated: 2025/04/25 16:36:17 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_data(t_data *data)
{
	data->is_dead = false;
	data->all_ate = false;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
	{
		printf("Error: malloc failed\n");
		return (false);
	}
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
	{
		printf("Error: malloc failed\n");
		free(data->forks);
		return (false);
	}
	return (true);
}

static bool	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			printf("Error: mutex initialization failed\n");
			return (false);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (false);
	if (pthread_mutex_init(&data->mealtime_mutex, NULL))
		return (false);
	if (pthread_mutex_init(&data->end_mutex, NULL))
		return (false);
	return (true);
}

static bool	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].nb_eat = 0;
		data->philos[i].last_meal_time = get_time_ms();
		data->philos[i].currently_eating = false;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		data->philos[i].data = data;
		i++;
	}
	return (true);
}

bool	init_simulation(t_data *data)
{
	if (!init_data(data))
		return (false);
	if (!init_mutexes(data))
		return (false);
	if (!init_philos(data))
		return (false);
	return (true);
}
