/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:00:06 by cgelgon           #+#    #+#             */
/*   Updated: 2025/04/23 14:01:06 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// void	opti_delay(t_philo *philo)
// {
// 	int		base_delay;
// 	t_data	*data;

// 	data = philo->data;
// 	base_delay = (data->time_to_eat * 200) / data->nb_philo;
// 	if (philo->id % 2 == 0)
// 		usleep(base_delay * (1 + philo->id % 10) / 5);
// 	if (data->nb_philo > 50 && philo->id > data->nb_philo / 2)
// 		usleep(base_delay);
// }

void opti_delay(t_philo *philo)
{
    t_data *data;
    int base_delay;

    data = philo->data;
    
    // Calcul d'un délai de base adapté au nombre de philosophes
    base_delay = 1000; // 1ms de base
    
    // Stratégie d'échelonnement:
    // 1. Délai progressif basé sur l'ID pour éviter que tous les philosophes 
    //    ne commencent en même temps
    usleep(base_delay * (philo->id % 3));
    
    // 2. Décalage entre pairs et impairs pour faciliter l'alternance
    if (philo->id % 2 == 0)
    {
        // Les philosophes pairs attendent un peu pour laisser les impairs prendre leurs fourchettes
        usleep(data->time_to_eat * 100); // 1/10 du temps de repas
    }
    
    // 3. Ajustement spécial pour un grand nombre de philosophes
    if (data->nb_philo > 20)
    {
        // Pour les grands groupes, échelonnez davantage les départs
        usleep(base_delay * (philo->id % 5));
    }
}

// Afficher le statut d'un philosophe
void	get_status(t_philo *philo, char *statut)
{
	long long	current_time;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!simulation_over(philo->data))
	{
		current_time = get_time_ms() - philo->data->start_time;
		printf("%lld %d %s\n", current_time, philo->id, statut);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	initialize_philosophers(t_data *data, int ac, char **av)
{
	if (!parse_args(data, ac, av))
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	if (!init_simulation(data))
	{
		printf("Error: simulation init failed\n");
		return (1);
	}
	return (0);	
}
