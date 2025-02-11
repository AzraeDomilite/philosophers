/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:57:49 by blucken           #+#    #+#             */
/*   Updated: 2025/02/11 12:59:45 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	get_child_philo(t_data *data, pid_t *pid)
{
	int	philo_exit_code;
	int	exit_code;

	if (*pid && waitpid(*pid, &philo_exit_code, WNOHANG) != 0)
	{
		if (WIFEXITED(philo_exit_code))
		{
			exit_code = WEXITSTATUS(philo_exit_code);
			if (exit_code == CHILD_EXIT_DEAD)
				return (kill_all_philos(data, 1));
			if (exit_code == CHILD_EXIT_PTHREAD_ERROR
				|| exit_code == CHILD_EXIT_SEM_ERROR)
				return (kill_all_philos(data, -1));
			if (exit_code == CHILD_EXIT_FULL)
			{
				data->philo_full_count += 1;
				return (1);
			}
		}
	}
	return (0);
}

bool	has_simulation_stopped(t_data *data)
{
	bool	ret;

	sem_wait(data->sem_stop);
	ret = data->sim_status;
	sem_post(data->sem_stop);
	return (ret);
}

int	stop_philo(t_data *data)
{
	size_t	index;
	int		exit_code;

	start_delay(data->start_timer);
	while (!has_simulation_stopped(data))
	{
		index = 0;
		while (index < data->nb_of_philos)
		{
			exit_code = get_child_philo(data, &data->pids[index]);
			if (exit_code == 1 || exit_code == -1)
			{
				sem_wait(data->sem_stop);
				data->sim_status = true;
				sem_post(data->sem_stop);
				sem_post(data->sem_philo_full);
				sem_post(data->sem_philo_dead);
				break ;
			}
			index++;
		}
		usleep(1000);
	}
	cleanup_zombies(data);
	return (0);
}

void	cleanup_zombies(t_data *data)
{
	size_t	index;

	index = 0;
	while (index < data->nb_of_philos)
	{
		if (data->pids[index] > 0)
			waitpid(data->pids[index], NULL, WNOHANG);
		index++;
	}
}
