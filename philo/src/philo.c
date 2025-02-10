/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:32:55 by blucken           #+#    #+#             */
/*   Updated: 2025/02/09 17:35:33 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief 
 * 
 * @param philo 
 * @param first 
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
 * @brief one philo can not eat, so he will just grab a fork
 * and wait for the death
 * 
 * @param philo 
 * @return void* just for null
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
 * @brief check the protected boolvar sim_status
 * 
 * @param data 
 * @return true continue the simulation
 * @return false to end the simulation
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
 * @brief even id start thinking, odd go for eat
 * adding a delay for sync starting
 * 
 * @param data 
 * @return void* 
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
