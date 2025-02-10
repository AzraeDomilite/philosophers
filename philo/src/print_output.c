/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:35:06 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 14:35:06 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Prints formatted status message for philosopher actions
 * 
 * @param philo Philosopher structure
 * @param str Status message to print
 * @param color ANSI color code for output
 * 
 * Formats and prints timestamped philosopher status messages
 * with optional color coding based on COLOR_MODE setting
 */
static void	print_status(t_philo *philo, char *str, char *color)
{
	if (COLOR_MODE)
		printf("%6ld %3d %s%s\n\e[0m", get_time() - philo->data->start_timer,
			philo->id + 1, color, str);
	else
		printf("%ld %d %s\n", get_time() - philo->data->start_timer,
			philo->id + 1, str);
}

/**
 * @brief Prints debug information during development
 * 
 * @param philo Philosopher structure
 * @param str Debug message
 * @param i Additional integer value for debugging
 * 
 * Thread-safe debug printing function that checks simulation status
 */
void	print_debug(t_philo *philo, char *str, int i)
{
	pthread_mutex_lock(&philo->data->print_lock);
	if (!all_philo_is_alive(philo->data))
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		return ;
	}
	printf("DEBUG : %s %i\n", str, i);
	pthread_mutex_unlock(&philo->data->print_lock);
}

/**
 * @brief Prints initial configuration data for debug cases
 * 
 * @param data Main program data structure
 * 
 * Displays all simulation parameters at startup
 */
void	print_data(t_data *data)
{
	printf("nb of philo 	: %ld\n", data->nb_of_philos);
	printf("time_to_die 	: %ld\n", data->time_to_die);
	printf("time_to_eat 	: %ld\n", data->time_to_eat);
	printf("time_to_sleep 	: %ld\n", data->time_to_sleep);
	printf("nb_must_eat 	: %d\n\n", data->nb_time_ph_must_eat);
}

/**
 * @brief Thread-safe status output function
 * 
 * @param philo Philosopher structure
 * @param monitor Whether called from monitor thread
 * @param status Type of status message to print
 * 
 * Handles all philosopher status messages with proper synchronization
 */
void	print_output(t_philo *philo, bool monitor, t_status status)
{
	pthread_mutex_lock(&philo->data->print_lock);
	if (!all_philo_is_alive(philo->data) && !monitor)
	{
		pthread_mutex_unlock(&philo->data->print_lock);
		return ;
	}
	if (status == DIE)
		print_status(philo, "died", RED);
	else if (status == EAT)
		print_status(philo, "is eating", PURPLE);
	else if (status == SLEEP)
		print_status(philo, "is sleeping", CYAN);
	else if (status == THINK)
		print_status(philo, "is thinking", GREEN);
	else if (status == FORK_1 || status == FORK_2)
		print_status(philo, "has taken a fork", ORANGE);
	pthread_mutex_unlock(&philo->data->print_lock);
}
