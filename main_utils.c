/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:00:06 by cgelgon           #+#    #+#             */
/*   Updated: 2025/04/22 15:42:15 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_data(t_data *data)
{
	data->is_dead = false;
	data->all_ate = false;
	data->start_time = get_time_ms();
	
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return false;
	data->philos = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philos)
	{
		free(data->forks);
		return false;
	}
	return true;
}


static bool	mutexes_init(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{	
			printf("Error: mutex initialization failed\n");
			return false;
		}
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
			return false;
	if (pthread_mutex_init(&data->mealtime_mutex, NULL))
			return false;
	if (pthread_mutex_init(&data->end_mutex, NULL))
			return false;
	return true;
}

static bool	philo_init(t_data *data)
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
	return true;
}

int	initialize_philosophers(t_data *data, int ac, char **av)
{
	if (!parse_args(data, ac, av))
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	if (!init_data(data))
	{
		printf("Error: memory allocation failed\n");
		return (1);
	}
	if (!mutexes_init(data))
	{
		cleanup(data);
		return (1);
	}
	if (!philo_init(data))
	{
		cleanup(data);
		return (1);
	}
	return (0);	
}
