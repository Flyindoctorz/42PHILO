/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:07:44 by cgelgon           #+#    #+#             */
/*   Updated: 2025/04/28 16:15:40 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	simulation_over(t_data *data)
{
	bool	end;

	pthread_mutex_lock(&data->end_mutex);
	end = (data->is_dead || data->all_ate);
	pthread_mutex_unlock(&data->end_mutex);
	return (end);
}

bool	check_death(t_data *data)
{
	t_time	time;

	time.i = 0;
	while (time.i < data->nb_philo)
	{
		pthread_mutex_lock(&data->mealtime_mutex);
		time.ct_time = get_time_ms();
		time.ed_time = time.ct_time - data->philos[time.i].last_meal_time;
		if (time.ed_time >= data->time_to_die
			&& !data->philos[time.i].currently_eating)
		{
			pthread_mutex_unlock(&data->mealtime_mutex);
			pthread_mutex_lock(&data->end_mutex);
			data->is_dead = true;
			pthread_mutex_unlock(&data->end_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf("%lld %d died\n", time.ct_time - data->start_time,
				data->philos[time.i].id);
			pthread_mutex_unlock(&data->print_mutex);
			return (true);
		}
		pthread_mutex_unlock(&data->mealtime_mutex);
		time.i++;
	}
	return (false);
}

bool	check_meals(t_data *data)
{
	int	i;
	int	finished_eating;

	if (data->nb_must_eat == -1)
		return (false);
	i = 0;
	finished_eating = 0;
	pthread_mutex_lock(&data->mealtime_mutex);
	while (i < data->nb_philo)
	{
		if (data->philos[i].nb_eat >= data->nb_must_eat)
			finished_eating++;
		i++;
	}
	pthread_mutex_unlock(&data->mealtime_mutex);
	if (finished_eating == data->nb_philo)
	{
		pthread_mutex_lock(&data->end_mutex);
		data->all_ate = true;
		pthread_mutex_unlock(&data->end_mutex);
		return (true);
	}
	return (false);
}
