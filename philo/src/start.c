/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:32:33 by blucken           #+#    #+#             */
/*   Updated: 2025/02/08 18:33:03 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Start the simulation, entry point for philo and monitoring functions.
 * 
 * @param data 
 * @return true is simulation start well
 * @return false in case of error
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
