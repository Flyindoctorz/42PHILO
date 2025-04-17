/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:03:41 by cgelgon           #+#    #+#             */
/*   Updated: 2025/04/17 11:54:55 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



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