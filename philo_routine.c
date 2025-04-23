/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:41:57 by cgelgon           #+#    #+#             */
/*   Updated: 2025/04/23 12:45:04 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// if alone
static void	*if_alone(void *philosophe)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philosophe;
	data = philo->data;
	pthread_mutex_lock(&philo->data->mealtime_mutex);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->data->mealtime_mutex);
	if (data->nb_philo == 1)
		return (if_alone(philo), NULL);
	opti_delay(philo);
	routine_core(philo);
	return (NULL);
}

// Routine principale d'un philosophe
void	*routine_philosophe(void *philosophe)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philosophe;
	data = philo->data;
	pthread_mutex_lock(&philo->data->mealtime_mutex);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->data->mealtime_mutex);
	if (data->nb_philo == 1)
		return (if_alone(philo), NULL);
	opti_delay(philo);
	routine_core(philo);
	return (NULL);
}
