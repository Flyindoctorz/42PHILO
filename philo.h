/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:40:36 by cgelgon           #+#    #+#             */
/*   Updated: 2025/03/31 13:40:38 by cgelgon          ###   ########.fr       */
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

typedef struct s_philo
{
	int			id;
	int			nb_eat;
	long long	last_meal_time;
	bool		currently_eating;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t	thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int			nb_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_must_eat;
	int			is_dead;
	long long	start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	mealtime_mutex;
	pthread_mutex_t	end_mutex;
	t_philo		*philos;
}	t_data;

/* Prototypes des fonctions utilitaires */
long long	obtenir_temps_ms(void);
void		attendre_ms(int ms);

/* Prototype de la routine du philosophe */
void		*routine_philosophe(void *philosophe);

#endif