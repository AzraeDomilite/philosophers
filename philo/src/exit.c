/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:32:49 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 14:33:02 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * Frees all allocated memory associated with the program data structure
 * 
 * @param data Pointer to the main data structure containing program information
 * @return Always returns NULL after freeing memory
 * 
 * This function performs cleanup by:
 * - Freeing each philosopher's data structure
 * - Freeing the array of philosopher pointers
 * - Freeing the fork locks array
 * - Freeing the main data structure itself
 * 
 * If data is NULL, returns NULL without performing any operations
 */
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

/**
 * @brief Destroys all mutexes used in the program
 * 
 * This static function safely destroys all mutex locks including:
 * - Fork mutexes for each philosopher
 * - Meal time mutexes for each philosopher
 * - Print lock for synchronized console output
 * - Simulation status lock
 * 
 * @param data Pointer to the main data structure containing all program information
 */
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

/**
 * @brief Stops all philosopher threads and performs cleanup
 * 
 * This function:
 * 1. Joins all philosopher threads
 * 2. Joins the monitor thread (if more than one philosopher exists)
 * 3. Destroys all mutexes
 * 4. Frees all allocated memory
 * 
 * @param data Pointer to the main data structure containing all program information
 */
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
