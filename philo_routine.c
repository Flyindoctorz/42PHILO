/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:41:57 by cgelgon           #+#    #+#             */
/*   Updated: 2025/03/31 14:02:17 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Vérifier si la simulation est terminée */
static int	simulation_over(t_data *data)
{
	int	end;

	end = 0;
	pthread_mutex_lock(&data->end_mutex);
	if (data->is_dead)
		end = 1;
	pthread_mutex_unlock(&data->end_mutex);
	return (end);
}

/* Afficher le statut d'un philosophe de manière thread-safe */
static void	get_status(t_philo *philo, char *statut)
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

/* Prendre les fourchettes pour manger */
static void	takeafork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		get_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		get_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		get_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		get_status(philo, "has taken a fork");
	}
}

/* Manger : mettre à jour l'heure du dernier repas et attendre */
static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mealtime_mutex);
	philo->currently_eating = 1;
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->data->mealtime_mutex);
	
	get_status(philo, "is eating");
	wait_ms(philo->data->time_to_eat);
	
	pthread_mutex_lock(&philo->data->mealtime_mutex);
	philo->nb_eat++;
	philo->currently_eating = 0;
	pthread_mutex_unlock(&philo->data->mealtime_mutex);
}

/* Routine principale d'un philosophe */
void	*routine_philosophe(void *philosophe)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philosophe;
	data = philo->data;
	if (philo->id % 2 != 0)
		usleep(1000);
	while (!simulation_over(data))
	{
		get_status(philo, "is thinking");
		takeafork(philo);
		eating(philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		get_status(philo, "is sleeping");
		wait_ms(data->time_to_sleep);
	}
	return (NULL);
}