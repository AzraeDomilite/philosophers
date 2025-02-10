/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:18:21 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 14:32:43 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Initializes fork mutexes
 * 
 * @param data Main program data structure
 * @return pthread_mutex_t* Array of initialized mutexes or NULL on error
 * 
 * Creates and initializes mutex for each fork in the simulation
 */
static pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	size_t			index;

	forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philos);
	if (!forks)
		return (null_error_msg(MALLOC_ERROR));
	index = 0;
	while (index < data->nb_of_philos)
	{
		if (pthread_mutex_init(&forks[index], 0) != 0)
			return (null_error_msg(MUTEX_ERROR));
		index++;
	}
	return (forks);
}

/**
 * @brief Populates data structure with command line arguments
 * 
 * @param data Data structure to fill
 * @param av Command line arguments array
 * 
 * Converts and stores all simulation parameters
 */
static void	fill_data(t_data *data, char **av)
{
	data->nb_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nb_time_ph_must_eat = ft_atoi(av[5]);
	else
		data->nb_time_ph_must_eat = -1;
}

/**
 * @brief Initializes all required mutexes
 * 
 * @param data Main program data structure
 * @return true If all mutexes initialize successfully
 * @return false If any mutex initialization fails
 */
static bool	init_mutex(t_data *data)
{
	if (!set(&data->fork_locks, init_forks(data)))
		return (false);
	if (pthread_mutex_init(&data->sim_status_lock, 0))
		return (free_data(data), error_msg(MUTEX_ERROR, false));
	if (pthread_mutex_init(&data->print_lock, 0))
		return (free_data(data), error_msg(MUTEX_ERROR, false));
	return (true);
}

/**
 * @brief Main initialization function
 * 
 * @param av Command line arguments array
 * @return t_data* Initialized data structure or NULL on error
 * 
 * Performs complete program initialization:
 * - Allocates main structure
 * - Sets up all philosophers
 * - Initializes all mutexes
 */
t_data	*init_data(char **av)
{
	t_data	*data;

	if (!set(&data, malloc(sizeof(t_data))))
		return (null_error_msg(MALLOC_ERROR));
	memset(data, 0, sizeof(t_data));
	fill_data(data, av);
	if (!set(&data->philos, init_philo(data)))
		return (NULL);
	if (!init_mutex(data))
		return (NULL);
	if (DEBUG_MODE)
		print_data(data);
	return (data);
}
