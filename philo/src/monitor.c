/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:32:35 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 14:32:36 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Updates simulation status in a thread-safe manner
 * 
 * @param data Main data structure
 * @param status New status to set
 */
static void	update_sim_status(t_data *data, bool status)
{
	pthread_mutex_lock(&data->sim_status_lock);
	data->sim_status = status;
	pthread_mutex_unlock(&data->sim_status_lock);
}

/**
 * @brief Checks if a philosopher has died
 * 
 * @param philo Philosopher to check
 * @return true If philosopher has died
 * @return false If philosopher is alive
 */
static bool	philo_is_dead(t_philo *philo)
{
	if ((get_time() - philo->last_meal_time) >= philo->data->time_to_die)
	{
		update_sim_status(philo->data, true);
		print_output(philo, true, DIE);
		pthread_mutex_unlock(&philo->meal_time_lock);
		return (true);
	}
	return (false);
}

/**
 * @brief Checks ending conditions for the simulation
 * 
 * @param data Main data structure
 * @return true If simulation should end
 * @return false If simulation should continue
 * 
 * Checks for:
 * - Dead philosophers
 * - All philosophers reached meal count
 */
static bool	end(t_data *data)
{
	size_t	index;
	size_t	nb_philo_reach_max_meals;

	index = 0;
	nb_philo_reach_max_meals = 0;
	while (index < (size_t)data->nb_of_philos)
	{
		pthread_mutex_lock(&data->philos[index]->meal_time_lock);
		if (philo_is_dead(data->philos[index]))
			return (true);
		if (data->nb_time_ph_must_eat != -1)
			if ((data->philos[index]->nb_meal_eat)
				>= (size_t)data->nb_time_ph_must_eat)
				nb_philo_reach_max_meals++;
		pthread_mutex_unlock(&data->philos[index]->meal_time_lock);
		index++;
	}
	if (nb_philo_reach_max_meals == (size_t)data->nb_of_philos
		&& data->nb_time_ph_must_eat != -1)
		return (update_sim_status(data, true), true);
	return (false);
}

/**
 * @brief Monitor thread routine
 * 
 * @param in_data Void pointer to main data structure
 * @return void* NULL
 * 
 * Continuously monitors:
 * - Philosopher death conditions
 * - Meal count requirements
 * - Overall simulation status
 */
void	*monitor(void *in_data)
{
	t_data	*data;

	data = (t_data *)in_data;
	if (!data->nb_time_ph_must_eat)
		return (NULL);
	update_sim_status(data, false);
	start_delay(data->start_timer);
	while (1)
	{
		if (end(data))
			return (NULL);
		usleep(1000);
	}
}
