/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:03:41 by cgelgon           #+#    #+#             */
/*   Updated: 2025/04/22 14:29:02 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool reaper_init(t_data *data)
{
	int	i;
	pthread_t	reaper;
	
	data->start_time = get_time_ms();
	i = 0;	
	while (i < data->nb_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, routine_philosophe,
				(void *)&data->philos[i]) != 0)
		{
			printf("Error: philos thread creation failed\n");
			return (false);
		}
		i++;
		if (pthread_create(&reaper, NULL, routine_philosophe,
				(void *)&data->philos[i]) != 0)
		{
			printf("Error: reaper thread creation failed\n");
			return (false);
		}
	}
	pthread_detach(reaper);
	return (true);
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			printf("Error: thread join failed\n");
			return ;
		}
		i++;
	}
}

void	cleanup(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->mealtime_mutex);
	pthread_mutex_destroy(&data->end_mutex);
	if (!data->philos)
		(free(data->philos));
}






int	main(int ac, char **av)
{
	t_data	data;

	if (ac <= 5 || ac >= 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat");
		printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");		
		return (1);
	}
	if (initialize_philosophers(&data, ac, av) == false)
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	if (!reaper_init(&data))
	{
		printf("Error: thread creation failed\n");
		cleanup(&data);
		return (1);
	}
	join_threads(&data);
	cleanup(&data);
	return (0);
}