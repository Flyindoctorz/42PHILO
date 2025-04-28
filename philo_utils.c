/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgelgon <cgelgon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:41:20 by cgelgon           #+#    #+#             */
/*   Updated: 2025/04/28 18:27:07 by cgelgon          ###   ########.fr       */
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

// //Fonction d'attente précise en millisecondes */
// void	wait_ms(int ms)
// {
// 	long long	start;
// 	start = get_time_ms();
// 	while (get_time_ms() - start < ms)
// 		usleep(100);
// }

void wait_ms(int ms)
{
    long long start;
    long long elapsed;
    long long remaining;
    
    start = get_time_ms();
    while (1) {
        elapsed = get_time_ms() - start;
        if (elapsed >= ms)
            break;
            
        // Calcul du temps restant
        remaining = ms - elapsed;
        
        // Pour les petites durées restantes, polling plus actif
        if (remaining < 5)
            usleep(100);
        else if (remaining < 20)
            usleep(500);
        else
            usleep(1000);  // Intervalles plus longs pour les longues attentes
    }
}

// void wait_ms(int ms)
// {
//     long long start;
//     long long elapsed;
//     start = get_time_ms();
    
//     // Pour les premiers 90% du temps, dormir par tranches de 500μs
//     long long target = ms * 9 / 10;
//     while ((elapsed = get_time_ms() - start) < target)
//         usleep(500);
    
//     // Pour les 10% restants, utiliser des tranches plus petites
//     while ((elapsed = get_time_ms() - start) < ms)
//         usleep(100);
// }

bool	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}
