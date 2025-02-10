/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:02:33 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 12:04:03 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*free_data(t_data *data)
{
	size_t	index;

	if (!data)
		return (NULL);
	index = 0;
	if (data->philos)
	{
		while (index < data->nb_of_philos)
		{
			if (data->philos[index])
				free(data->philos[index]);
			index++;
		}
		free(data->philos);
	}
	if (data->fork_locks)
		free(data->fork_locks);
	free(data);
	return (NULL);
}

static void	destroy_mutex(t_data *data)
{
	size_t	index;

	if (!data)
		return ;
	index = 0;
	while (index < data->nb_of_philos)
	{
		if (data->fork_locks)
			pthread_mutex_destroy(&data->fork_locks[index]);
		if (data->philos && data->philos[index])
			pthread_mutex_destroy(&data->philos[index]->meal_time_lock);
		index++;
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->sim_status_lock);
}

void	stop_philo(t_data *data)
{
	size_t	index;

	if (!data)
		return ;
	index = 0;
	while (index < data->nb_of_philos)
	{
		if (data->philos && data->philos[index])
			pthread_join(data->philos[index]->thread, NULL);
		index++;
	}
	if (data->nb_of_philos > 1)
		pthread_join(data->monitor, NULL);
	destroy_mutex(data);
	free_data(data);
}
