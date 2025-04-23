/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_core.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:32:54 by cgelgon           #+#    #+#             */
/*   Updated: 2025/04/23 14:10:18 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// // commence a manger
// static void	init_meal_time(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->mealtime_mutex);
// 	philo->last_meal_time = get_time_ms();
// 	pthread_mutex_unlock(&philo->data->mealtime_mutex);
// }
// pense
static void	think_status(t_philo *philo)
{
	get_status(philo, "is thinking");
}
// Prendre les fourchettes pour manger
static void takeafork(t_philo *philo)
{
    t_data *data;

    data = philo->data;
	
	if (philo->id % 2 == 0)
	{
        pthread_mutex_lock(philo->left_fork);
        get_status(philo, "has taken a fork");
		if (simulation_over(data))
		{
			(pthread_mutex_unlock(philo->left_fork));
			return ;
		}
        pthread_mutex_lock(philo->right_fork);
        get_status(philo, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        get_status(philo, "has taken a fork");
		if (simulation_over(data))
			(pthread_mutex_unlock(philo->left_fork));
        pthread_mutex_lock(philo->right_fork);
        get_status(philo, "has taken a fork");
    }
}
// Manger : mettre à jour l'heure du dernier repas et attendre
static void just_do_eat(t_philo *philo)
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

void	routine_core(t_philo *philo)
{
	t_data *data;

	data = philo->data;
	while (!simulation_over(data))
	{
		think_status(philo);
		if (simulation_over(data))
			break ;
		takeafork(philo);
		if (simulation_over(data))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			break ;
		}
		just_do_eat(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (simulation_over(data))
			break ;
		get_status(philo, "is sleeping");
		wait_ms(data->time_to_sleep);
	}
}