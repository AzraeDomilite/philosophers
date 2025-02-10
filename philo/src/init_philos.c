/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 19:02:27 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 14:32:28 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Assigns fork IDs to philosopher
 * 
 * @param philo Philosopher structure to configure
 * 
 * Implements deadlock prevention by assigning forks in different order
 * for odd and even numbered philosophers
 */
static void	fill_fork_data(t_philo *philo)
{
	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->data->nb_of_philos;
	if (philo->id % 2)
	{
		philo->fork[0] = (philo->id + 1) % philo->data->nb_of_philos;
		philo->fork[1] = philo->id;
	}
}

/**
 * @brief Creates and initializes all philosopher structures
 * 
 * @param data Main program data structure
 * @return t_philo** Array of initialized philosopher structures or NULL on error
 * 
 * Allocates and initializes:
 * - Philosopher structures
 * - Meal time mutexes
 * - Fork assignments
 */
t_philo	**init_philo(t_data *data)
{
	t_philo	**philos;
	size_t	index;

	index = 0;
	if (!set(&philos, malloc(sizeof(t_philo) * data->nb_of_philos)))
		return (null_error_msg(MALLOC_ERROR));
	while (index < data->nb_of_philos)
	{
		if (!set(&philos[index], malloc(sizeof(t_philo))))
			return (null_error_msg(MALLOC_ERROR));
		memset(philos[index], 0, sizeof(t_philo));
		if (pthread_mutex_init(&philos[index]->meal_time_lock, 0))
			return (null_error_msg(MUTEX_ERROR));
		philos[index]->id = index;
		philos[index]->data = data;
		fill_fork_data(philos[index]);
		index++;
	}
	return (philos);
}
