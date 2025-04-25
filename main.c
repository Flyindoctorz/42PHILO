/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:03:41 by cgelgon           #+#    #+#             */
/*   Updated: 2025/04/25 14:58:24 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// // Initialiser les philosophes et reaper
// static bool	init_threads(t_data *data)
// {
// 	int			i;
// 	pthread_t	reaper;

// 	data->start_time = get_time_ms();
//     i = 0;	
// 	while (i < data->nb_philo)
// 	{
// 		data->philos[i].last_meal_time = data->start_time;
// 		if (pthread_create(&data->philos[i].thread, NULL, routine_philosophe,
// 				(void *)&data->philos[i]) != 0)
// 		{
// 			printf("Error: philos thread creation failed\n");
// 			return (false);
// 		}
// 		i++;
// 	}
// 	usleep(5000);
// 	if (pthread_create(&reaper, NULL, reaper_routine,
// 				(void *)data) != 0)
// 	{
// 		printf("Error: reaper thread creation failed\n");
// 		return (false);
// 	}
// 	pthread_detach(reaper);
// 	// pthread_join(data->)
// 	return (true);
// }

// void	join_threads(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->nb_philo)
// 	{
// 		if (pthread_join(data->philos[i].thread, NULL) != 0)
// 		{
// 			printf("Error: thread join failed\n");
// 			return ;
// 		}
// 		i++;
// 	}
// 	pthread_mutex_lock(&data->print_mutex);
//     pthread_mutex_unlock(&data->print_mutex);
// }



// int	main(int ac, char **av)
// {
// 	t_data data;

// 	if (ac < 5 || ac > 6)
// 	{
// 		printf("Usage: ./philo number_of_philosophers time_to_die");
// 		printf(" time_to_eat time_to_sleep");
// 		printf("[number_of_times_each_philosopher_must_eat]\n");
// 		return (1);
// 	}
// 	if (initialize_philosophers(&data, ac, av) != 0)
// 		return (1);
// 	if (!init_threads(&data))
// 	{
// 		cleanup(&data);
// 		return (1);
// 	}
// 	join_threads(&data);
// 	cleanup(&data);
// 	return (0);
// }

// Dans main.c - Modification pour supprimer le thread reaper détaché
static bool init_threads(t_data *data)
{
    int i;

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

// Remplacer join_threads par une fonction qui gère la surveillance et la jointure
void monitor_and_join(t_data *data)
{
    int i;
    
    // Boucle de surveillance qui remplace le reaper
    while (!simulation_over(data))
    {
        if (check_death(data) || check_meals(data))
            break;
        usleep(500);
    }
    pthread_mutex_lock(&data->end_mutex);
    data->is_dead = true;
    pthread_mutex_unlock(&data->end_mutex);
    for (i = 0; i < data->nb_philo; i++)
    {
        pthread_join(data->philos[i].thread, NULL);
    }
	usleep(100);
}

// Modification du main pour utiliser la nouvelle fonction
int main(int ac, char **av)
{
    t_data data;

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
    
    // Remplacer join_threads par monitor_and_join
    monitor_and_join(&data);
    cleanup(&data);
    return (0);
}