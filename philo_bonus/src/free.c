/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:51:24 by blucken           #+#    #+#             */
/*   Updated: 2025/02/11 13:56:01 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
static void	close_philo_sem(t_philo *philo)
{
	sem_close(philo->sem_forks);
	sem_close(philo->sem_philo_dead);
	sem_close(philo->sem_philo_full);
	sem_close(philo->sem_write);
	sem_close(philo->sem_meal);
}

static void close_data_sem(t_data *data)
{
	if (data->pids)
		free(data->pids);
	if (data->ate_enought_monitor)
		pthread_join(data->ate_enought_monitor, NULL);
	if (data->death_monitor)
		pthread_join(data->death_monitor, NULL);
	sem_close(data->sem_forks);
	sem_close(data->sem_write);
	sem_close(data->sem_philo_full);
	sem_close(data->sem_philo_dead);
	sem_close(data->sem_stop);
}

void	*free_data(t_data *data)
{
	size_t	index;

	if (!data)
		return (NULL);
	if (data->philos)
	{
		index = 0;
		while (index < data->nb_of_philos)
		{
			if (data->philos[index])
			{
				close_philo_sem(data->philos[index]);
				if (data->philos[index]->sem_meal_name)
					free(data->philos[index]->sem_meal_name);
				free(data->philos[index++]);
			}
		}
		free(data->philos);
	}
	close_data_sem(data);
	free(data);
	return (NULL);
}

int	sem_error_cleanup(t_data *data)
{
	sem_close(data->sem_forks);
	sem_close(data->sem_write);
	sem_close(data->sem_philo_full);
	sem_close(data->sem_philo_dead);
	sem_close(data->sem_stop);
	unlink_sems();
	return (error_failure(SEM_ERROR, data));
}

int	data_cleanup(t_data *data, int exit_code)
{
	if (data)
	{
		if (data->ate_enought_monitor)
			pthread_join(data->ate_enought_monitor, NULL);
		if (data->death_monitor)
			pthread_join(data->death_monitor, NULL);
		sem_close(data->sem_forks);
		sem_close(data->sem_write);
		sem_close(data->sem_philo_full);
		sem_close(data->sem_philo_dead);
		sem_close(data->sem_stop);
		free_data(data);
	}
	return (exit_code);
}
