/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:58:56 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 12:59:48 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

bool	start_philo(t_data *data)
{
	size_t	index;
	pid_t	pid;

	data->start_timer = get_time() + (data->nb_of_philos * 2);
	index = 0;
	while (index < data->nb_of_philos)
	{
		sem_unlink(data->philos[index]->sem_meal_name);
		data->philos[index]->sem_meal = sem_open(data->philos[index]
				->sem_meal_name, O_CREAT, S_IRUSR | S_IWUSR, 1);
		if (data->philos[index]->sem_meal == SEM_FAILED)
			return (false);
		pid = fork();
		if (pid == -1)
			return (kill_all_philos(data, 1), error_msg(FORK_ERROR, false));
		if (pid == 0)
		{
			data->current_philo = data->philos[index];
			philo(data);
			_exit(0);
		}
		data->pids[index++] = pid;
	}
	return (tread_monitor(data));
}
