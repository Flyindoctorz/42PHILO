/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:00:06 by cgelgon           #+#    #+#             */
/*   Updated: 2025/04/28 18:32:41 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	opti_delay(t_philo *philo)
// {
// 	t_data	*data;
// 	int		base_delay;

// 	data = philo->data;
// 	base_delay = 1000;
// 	usleep(base_delay * (philo->id % 3));
// 	if (philo->id % 2 == 0)
// 		usleep(data->time_to_eat * 100);
// 	if (data->nb_philo > 20)
// 		usleep(base_delay * (philo->id % 5));
// }

// void opti_delay(t_philo *philo)
// {
//     t_data *data;
//     int base_delay;
    
//     data = philo->data;
//     base_delay = 500;  // Réduire le délai de base
    
//     // Philosophes pairs et impairs ont des délais différents
//     if (philo->id % 2 == 0) {
//         usleep(base_delay);
//     } else {
//         // Pour les impairs, délai proportionnel au temps de manger
//         usleep(data->time_to_eat * 800);
//     }
    
//     // Pour les très grands nombres de philosophes, ajouter une distribution supplémentaire
//     if (data->nb_philo > 100) {
//         usleep(base_delay * (philo->id % 7));  // Distribution modulo 7
//     }
// }

void opti_delay(t_philo *philo)
{
    t_data *data;
    
    data = philo->data;
    
    // Distribution initiale différente selon parité
    if (philo->id % 2 == 1) { // Pour les philosophes impairs
        // Délai plus court pour leur permettre de commencer plus tôt
        usleep(500);
    } else { // Pour les philosophes pairs
        // Délai suffisant pour que les impairs prennent leurs fourchettes d'abord
        usleep(data->time_to_eat / 2 * 1000);
    }
}

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
