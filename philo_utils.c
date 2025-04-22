/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:41:20 by cgelgon           #+#    #+#             */
/*   Updated: 2025/03/31 14:02:44 by cgelgon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Obtenir le temps actuel en millisecondes */
long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/* Fonction d'attente précise en millisecondes */
void	wait_ms(int ms)
{
	long long	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
		usleep(100);
}