/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:03:41 by cgelgon           #+#    #+#             */
/*   Updated: 2025/04/28 18:27:43 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	init_threads(t_data *data)
{
	int	i;

	data->start_time = get_time_ms();
	i = 0;
	while (i < data->nb_philo)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL, routine_philosophe,
				(void *)&data->philos[i]) != 0)
		{
			printf("Error: philos thread creation failed\n");
			return (false);
		}
		i++;
	}
	return (true);
}

// void	monitor_and_join(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (!simulation_over(data))
// 	{
// 		if (check_death(data) || check_meals(data))
// 			break ;
// 		usleep(100);
// 	}
// 	pthread_mutex_lock(&data->end_mutex);
// 	data->is_dead = true;
// 	pthread_mutex_unlock(&data->end_mutex);
// 	while (i < data->nb_philo)
// 	{
// 		pthread_join(data->philos[i].thread, NULL);
// 		i++;
// 	}
// 	usleep(100);
// }

void monitor_and_join(t_data *data)
{
    int i;
    int check_interval;
    
    // Adapter l'intervalle de vérification selon le nombre de philosophes
    check_interval = (data->nb_philo > 100) ? 1000 : 500;
    
    while (!simulation_over(data)) {
        // Vérifier la mort moins fréquemment pour les grands nombres
        if (check_death(data) || check_meals(data))
            break;
        usleep(check_interval);
    }
    
    pthread_mutex_lock(&data->end_mutex);
    data->is_dead = true;
    pthread_mutex_unlock(&data->end_mutex);
    
    i = 0;
    while (i < data->nb_philo) {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philo number_of_philosophers time_to_die");
		printf(" time_to_eat time_to_sleep");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	if (initialize_philosophers(&data, ac, av) != 0)
		return (1);
	if (!init_threads(&data))
	{
		cleanup(&data);
		return (1);
	}
	monitor_and_join(&data);
	cleanup(&data);
	return (0);
}
