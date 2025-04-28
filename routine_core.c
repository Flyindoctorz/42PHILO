/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:32:54 by cgelgon           #+#    #+#             */
/*   Updated: 2025/04/28 18:37:35 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	think_status(t_philo *philo)
{
	get_status(philo, "is thinking");
}

static int	take_forkita(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	get_status(philo, "has taken a fork");
	if (simulation_over(philo->data))
	{
		pthread_mutex_unlock(fork);
		return (1);
	}
	return (0);
}

static void	takeafork(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	if (take_forkita(philo, first_fork))
		return ;
	if (take_forkita(philo, second_fork))
	{
		pthread_mutex_unlock(first_fork);
		return ;
	}
}
// static void takeafork(t_philo *philo)
// {
//     pthread_mutex_t *first_fork;
//     pthread_mutex_t *second_fork;
    
//     if (philo->id % 2 == 0) {
//         first_fork = philo->right_fork;
//         second_fork = philo->left_fork;
//     } else {
//         first_fork = philo->left_fork;
//         second_fork = philo->right_fork;
//     }
    
//     pthread_mutex_lock(first_fork);
//     get_status(philo, "has taken a fork");
//     if (simulation_over(philo->data)) {
//         pthread_mutex_unlock(first_fork);
//         return;
//     }
    
//     // // Ajout d'un court délai pour les philosophes impairs uniquement
//     // if (philo->id % 2 == 1 && philo->data->nb_philo > 100)
//     //     usleep(500);
        
//     pthread_mutex_lock(second_fork);
//     get_status(philo, "has taken a fork");
//     if (simulation_over(philo->data)) {
//         pthread_mutex_unlock(second_fork);
//         pthread_mutex_unlock(first_fork);
//         return;
//     }
// }

// Manger : mettre à jour l'heure du dernier repas et attendre
static void	just_do_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mealtime_mutex);
	philo->last_meal_time = get_time_ms();
	philo->currently_eating = true;
	pthread_mutex_unlock(&philo->data->mealtime_mutex);
	get_status(philo, "is eating");
	wait_ms(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->mealtime_mutex);
	philo->nb_eat++;
	philo->currently_eating = false;
	pthread_mutex_unlock(&philo->data->mealtime_mutex);
}
// static void just_do_eat(t_philo *philo)
// {
//     long long current_time;
    
//     // Capture le temps actuel avant de verrouiller
//     current_time = get_time_ms();
    
//     // Verrouille brièvement pour mettre à jour les données
//     pthread_mutex_lock(&philo->data->mealtime_mutex);
//     philo->last_meal_time = current_time;
//     philo->currently_eating = true;
//     pthread_mutex_unlock(&philo->data->mealtime_mutex);
    
//     // Affiche le statut (sans mutex mealtime)
//     get_status(philo, "is eating");
    
//     // Attente sans mutex
//     wait_ms(philo->data->time_to_eat);
    
//     // Verrouille brièvement pour mettre à jour les données
//     pthread_mutex_lock(&philo->data->mealtime_mutex);
//     philo->nb_eat++;
//     philo->currently_eating = false;
//     pthread_mutex_unlock(&philo->data->mealtime_mutex);
// }

static void release_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
    }
    else
    {
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
    }
}


void	routine_core(t_philo *philo)
{
	t_data	*data;
	bool	has_forks;

	data = philo->data;
	has_forks = false;
	while (!simulation_over(data) && philo->nb_eat != data->nb_must_eat)
	{
		think_status(philo);
		if (simulation_over(data))
			break ;
		takeafork(philo);
		has_forks = !simulation_over(data);
		if (!has_forks)
			break ;
		just_do_eat(philo);
		release_forks(philo);
		if (simulation_over(data))
			break ;
		get_status(philo, "is sleeping");
		wait_ms(data->time_to_sleep);
	}
}
