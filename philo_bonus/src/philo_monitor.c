/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:17:40 by blucken           #+#    #+#             */
/*   Updated: 2025/02/11 12:19:13 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static bool	end(t_data *data, t_philo *philo)
{
	sem_wait(philo->sem_meal);
	if (get_time() - philo->last_meal_time >= data->time_to_die)
	{
		print_output(philo, true, DIE);
		sem_post(data->current_philo->sem_philo_dead);
		sem_post(philo->sem_meal);
		return (true);
	}
	if (data->nb_time_ph_must_eat != -1 && philo->ate_enough == false
		&& philo->nb_meal_eat >= (unsigned int)data->nb_time_ph_must_eat)
	{
		sem_post(philo->sem_philo_full);
		philo->ate_enough = true;
	}
	sem_post(philo->sem_meal);
	return (false);
}

void	*philo_monitor(void *data_monitor)
{
	t_data	*data;

	data = (t_data *)data_monitor;
	if (data->nb_time_ph_must_eat == 0)
		return (NULL);
	sem_wait(data->current_philo->sem_philo_dead);
	sem_wait(data->current_philo->sem_philo_full);
	start_delay(data->start_timer);
	while (!end(data, data->current_philo))
	{
		usleep(1000);
		continue ;
	}
	return (NULL);
}
