/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:07:44 by cgelgon           #+#    #+#             */
/*   Updated: 2025/04/25 15:07:19 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	simulation_over(t_data *data)
{
	bool	end;

	pthread_mutex_lock(&data->end_mutex);
	end = data->is_dead || data->all_ate;
	pthread_mutex_unlock(&data->end_mutex);
	return (end);
}
bool	check_death(t_data *data)
{
	int	i;
	long long	current_time;
	long long	elapsed_time;

	i = 0;
	while(i < data->nb_philo)
	{
		pthread_mutex_lock(&data->mealtime_mutex);
		current_time = get_time_ms();
		elapsed_time = current_time - data->philos[i].last_meal_time;
		if (elapsed_time >= data->time_to_die && !data->philos[i].currently_eating)
		{
			pthread_mutex_unlock(&data->mealtime_mutex);
			pthread_mutex_lock(&data->end_mutex);
			data->is_dead = true;
			pthread_mutex_unlock(&data->end_mutex);
			pthread_mutex_lock(&data->print_mutex);
			printf("%lld %d died\n", current_time - data->start_time, data->philos[i].id);
			pthread_mutex_unlock(&data->print_mutex);
			return (true);
		}
		pthread_mutex_unlock(&data->mealtime_mutex);
		i++;
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

// void	*reaper_routine(void *data)
// {
// 	t_data	*data_ptr;

// 	data_ptr = (t_data *)data;
// 	while (!simulation_over(data_ptr))
// 	{
// 		if (check_death(data_ptr) || check_meals(data_ptr))
// 			break ;
// 		usleep(500);
// 	}
// 	return (NULL);
// }