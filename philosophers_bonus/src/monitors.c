/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:40:34 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 11:40:43 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	kill_all_philos(t_data *data, int exit_code)
{
	size_t	index;

	index = 0;
	while (index < data->nb_of_philos)
	{
		if (data->pids[index] > 0)
		{
			kill(data->pids[index], SIGKILL);
			waitpid(data->pids[index], NULL, 0);
		}
		index++;
	}
	return (exit_code);
}

void	*ate_enought_monitor(void *data_monitor)
{
	t_data	*data;

	data = (t_data *)data_monitor;
	if (data->nb_time_ph_must_eat < 0 || data->time_to_die == 0
		|| data->nb_of_philos == 1)
		return (NULL);
	start_delay(data->start_timer);
	while (data->philo_full_count < data->nb_of_philos)
	{
		if (has_simulation_stopped(data))
			return (NULL);
		sem_wait(data->sem_philo_full);
		if (!has_simulation_stopped(data))
			data->philo_full_count += 1;
		else
			return (NULL);
	}
	sem_wait(data->sem_stop);
	data->sim_status = true;
	kill_all_philos(data, EXIT_SUCCESS);
	sem_post(data->sem_philo_dead);
	sem_post(data->sem_stop);
	return (NULL);
}

void	*death_monitor(void *data_monitor)
{
	t_data	*data;

	data = (t_data *)data_monitor;
	if (data->nb_of_philos == 1)
		return (NULL);
	start_delay(data->start_timer);
	if (has_simulation_stopped(data) == true)
		return (NULL);
	sem_wait(data->sem_philo_dead);
	if (has_simulation_stopped(data) == true)
		return (NULL);
	sem_wait(data->sem_stop);
	data->sim_status = true;
	kill_all_philos(data, EXIT_SUCCESS);
	sem_post(data->sem_philo_full);
	sem_post(data->sem_stop);
	return (NULL);
}

bool	tread_monitor(t_data *data)
{
	if (pthread_create(&data->ate_enought_monitor, NULL,
			&ate_enought_monitor, data) == 0
		&& pthread_create(&data->death_monitor, NULL,
			&death_monitor, data) == 0)
		return (true);
	if (data->ate_enought_monitor)
		pthread_join(data->ate_enought_monitor, NULL);
	return (error_failure(THREAD_ERROR, data));
}
