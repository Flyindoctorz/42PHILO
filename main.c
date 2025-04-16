/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:03:41 by cgelgon           #+#    #+#             */
/*   Updated: 2025/03/31 15:18:28 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static bool	parse_args(t_data *data, int ac, char **av)
{
	data->nb_philo = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	if (ac == 6)
	data->nb_must_eat = atoi(av[5]);
	else
		data->nb_must_eat = -1;
	if (data->nb_philo <= 2 || data->time_to_die <= 0 || data->time_to_eat <= 0 ||
		data->time_to_sleep <= 0 || (ac == 6 && data->nb_must_eat <= 0))
		return false;
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

static bool	forks_init(t_data *data)
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
	return true;
}
static bool	philos_init(t_data *data)
{
	int	i;
	
	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].nb_eat = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].currently_eating = false;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		data->philos[i].data = data;
		if (pthread_create(&data->philos[i].thread, NULL, routine_philosophe, &data->philos[i]))
		{
			printf("Error: thread creation failed\n");
			return false;
		}
		i++;
	}
	return true;
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (!parse_args(&data, ac, av))
	{
		printf("Invalid arguments\n");
		return (1);
	}
	if (!mutexes_init(&data))
		return (1);
	if (!forks_init(&data))
		return (1);
	if (!philos_init(&data))
		return (1);
	
	// Initialiser les mutex // 
	// Initialiser les fourchettes
	// Initialiser les philos
	// Lancer les threads
	// Attendre la fin des threads
	// Libérer les ressources
	return (0);
}