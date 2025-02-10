/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 18:59:33 by blucken           #+#    #+#             */
/*   Updated: 2025/02/08 19:02:10 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	update_sim_status(t_data *data, bool status)
{
	pthread_mutex_lock(&data->sim_status_lock);
	data->sim_status = status;
	pthread_mutex_unlock(&data->sim_status_lock);
}

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
