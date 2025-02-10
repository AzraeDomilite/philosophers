/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:31:26 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 14:31:29 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Initializes and starts all philosopher threads and monitor thread
 * 
 * @param data Main data structure containing program configuration
 * @return true If all threads are created successfully
 * @return false If thread creation fails
 * 
 * Sets up the start timer with a staggered delay based on number of philosophers.
 * Creates threads for each philosopher and a monitor thread if there's more than one philosopher.
 */
bool	start_philo(t_data *data)
{
	size_t	index;

	index = 0;
	data->start_timer = get_time() + (data->nb_of_philos * 20);
	while (index < data->nb_of_philos)
	{
		if (pthread_create(&data->philos[index]->thread, NULL,
				&philo, data->philos[index]))
			return (error_msg(THREAD_ERROR, false));
		index++;
	}
	if (data->nb_of_philos > 1)
	{
		if (pthread_create(&data->monitor, NULL, &monitor, data))
			return (error_msg(THREAD_ERROR, false));
	}
	return (true);
}
