/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:32:55 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 14:32:35 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Manages philosopher's thinking state
 * 
 * @param philo Philosopher structure
 * @param first Boolean indicating if this is the first thinking period
 * 
 * Calculates optimal thinking time based on:
 * - Time since last meal
 * - Time to die
 * - Time needed to eat
 * Prevents starvation by adjusting thinking duration
 */
static void	philo_think(t_philo *philo, bool first)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_time_lock);
	time_to_think = (philo->data->time_to_die
			- (get_time() - philo->last_meal_time)
			- philo->data->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && first == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	print_output(philo, false, THINK);
	philo_sleep(philo->data, time_to_think);
}

/**
 * @brief Handles eating and sleeping cycle for a philosopher
 * 
 * @param philo Philosopher structure
 * 
 * Sequence:
 * 1. Acquires both forks
 * 2. Eats for specified duration
 * 3. Updates meal count and timestamp
 * 4. Sleeps for specified duration
 * 5. Releases forks
 */
static void	philo_eat_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_locks[philo->fork[0]]);
	print_output(philo, false, FORK_1);
	pthread_mutex_lock(&philo->data->fork_locks[philo->fork[1]]);
	print_output(philo, false, FORK_2);
	print_output(philo, false, EAT);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_time_lock);
	philo_sleep(philo->data, philo->data->time_to_eat);
	if (all_philo_is_alive(philo->data))
	{
		pthread_mutex_lock(&philo->meal_time_lock);
		philo->nb_meal_eat += 1;
		pthread_mutex_unlock(&philo->meal_time_lock);
	}
	print_output(philo, false, SLEEP);
	pthread_mutex_unlock(&philo->data->fork_locks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->data->fork_locks[philo->fork[0]]);
	philo_sleep(philo->data, philo->data->time_to_sleep);
}

/**
 * @brief Special case handler for single philosopher scenario
 * 
 * @param philo Philosopher structure
 * @return void* NULL
 * 
 * Handles the case where only one philosopher exists:
 * - Takes one fork
 * - Waits until death
 * - No eating possible with single fork
 */
static void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork_locks[philo->fork[0]]);
	print_output(philo, true, FORK_1);
	philo_sleep(philo->data, philo->data->time_to_die);
	print_output(philo, true, DIE);
	pthread_mutex_unlock(&philo->data->fork_locks[philo->fork[0]]);
	return (NULL);
}

/**
 * @brief Checks if simulation should continue
 * 
 * @param data Main data structure
 * @return true Continue simulation
 * @return false End simulation
 * 
 * Thread-safe check of simulation status using mutex protection
 */
bool	all_philo_is_alive(t_data *data)
{
	bool	status;

	status = false;
	pthread_mutex_lock(&data->sim_status_lock);
	status = !data->sim_status;
	pthread_mutex_unlock(&data->sim_status_lock);
	return (status);
}

/**
 * @brief Main philosopher routine running as a thread
 * 
 * @param data Void pointer to philosopher structure
 * @return void* NULL
 * 
 * Implements the philosopher's lifecycle:
 * - Handles initialization
 * - Manages eating/thinking/sleeping cycles
 * - Implements staggered start for even/odd philosophers
 * - Continues until simulation ends
 */
void	*philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (!philo->data->nb_time_ph_must_eat)
		return (NULL);
	pthread_mutex_lock(&philo->meal_time_lock);
	philo->last_meal_time = philo->data->start_timer;
	pthread_mutex_unlock(&philo->meal_time_lock);
	start_delay(philo->data->start_timer);
	if (!philo->data->time_to_die)
		return (NULL);
	if (philo->data->nb_of_philos == 1)
		return (one_philo(philo));
	if (philo->id % 2)
		philo_think(philo, true);
	if (philo->data->nb_of_philos - 1 == philo->id
		&& philo->data->nb_of_philos % 2)
		philo_think(philo, true);
	while (all_philo_is_alive(philo->data))
	{
		philo_eat_sleep(philo);
		philo_think(philo, false);
	}
	return (NULL);
}
