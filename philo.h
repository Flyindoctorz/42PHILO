/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:40:36 by cgelgon           #+#    #+#             */
/*   Updated: 2025/04/22 14:24:29 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdbool.h>
# include <string.h>
# include <limits.h>

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	long long		last_meal_time;
	bool			currently_eating;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_must_eat;
	bool			all_ate;
	int				is_dead;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	mealtime_mutex;
	pthread_mutex_t	end_mutex;
	t_philo			*philos;
}	t_data;

long long	get_time_ms(void);
void		wait_ms(int ms);


int		initialize_philosophers(t_data *data, int ac, char **av);

void	*routine_philosophe(void *philosophe);

void		cleanup(t_data *data);



#endif