/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:00:31 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 13:00:51 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*free_data(t_data *data)
{
	size_t	i;

	if (!data)
		return (NULL);
	if (data->philos)
	{
		i = 0;
		while (i < data->nb_of_philos)
		{
			if (data->philos[i])
			{
				if (data->philos[i]->sem_meal)
					sem_close(data->philos[i]->sem_meal);
				if (data->philos[i]->sem_meal_name)
					free(data->philos[i]->sem_meal_name);
				free(data->philos[i++]);
			}
		}
		free(data->philos);
	}
	if (data->pids)
		free(data->pids);
	sem_error_cleanup(data);
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
