/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:32:09 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 14:34:24 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Gets current time in milliseconds
 * 
 * @return time_t Current time in milliseconds since epoch
 * 
 * Uses gettimeofday for microsecond precision
 */
time_t	get_time(void)
{
	struct timeval		tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * @brief Delays execution until specified start time
 * 
 * @param start_time Target time to wait for
 * 
 * Busy wait implementation for precise timing
 */
void	start_delay(time_t start_time)
{
	(void)start_time;
	while (get_time() < start_time)
		continue ;
}

/**
 * @brief Custom sleep implementation for philosophers
 * 
 * @param data Program data structure
 * @param sleep_time Time to sleep in milliseconds
 * 
 * Features:
 * - Checks simulation status during sleep
 * - Uses small usleep intervals for precision
 * - Prevents oversleeping
 */
void	philo_sleep(t_data *data, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time() + sleep_time;
	while (get_time() < wake_up)
	{
		if (!all_philo_is_alive(data))
			break ;
		usleep(100);
	}
}
