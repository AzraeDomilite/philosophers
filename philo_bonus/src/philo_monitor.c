/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:35:31 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 12:36:28 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static bool	end(t_data *data)
{
	bool	status;

	status = false;
	sem_wait(data->sem_stop);
	status = data->sim_status;
	sem_post(data->sem_stop);
	return (status);
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
	while (!end(data))
	{
		usleep(1000);
		continue ;
	}
	return (NULL);
}
