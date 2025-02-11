/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:23:09 by blucken           #+#    #+#             */
/*   Updated: 2025/02/11 13:24:02 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	fill_data(t_data *data, char **av)
{
	data->nb_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->nb_time_ph_must_eat = ft_atoi(av[5]);
	else
		data->nb_time_ph_must_eat = -1;
}

bool	init_sem(t_data *data)
{
	unlink_sems();
	data->sem_forks = sem_open(SEM_NAME_FORKS, O_CREAT,
			S_IRUSR | S_IWUSR, data->nb_of_philos);
	if (data->sem_forks == SEM_FAILED)
		return (sem_error_cleanup(data));
	data->sem_write = sem_open(SEM_NAME_WRITE, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (data->sem_write == SEM_FAILED)
		return (sem_error_cleanup(data));
	data->sem_philo_full = sem_open(SEM_NAME_FULL, O_CREAT,
			S_IRUSR | S_IWUSR, data->nb_of_philos);
	if (data->sem_philo_full == SEM_FAILED)
		return (sem_error_cleanup(data));
	data->sem_philo_dead = sem_open(SEM_NAME_DEAD, O_CREAT,
			S_IRUSR | S_IWUSR, data->nb_of_philos);
	if (data->sem_philo_dead == SEM_FAILED)
		return (sem_error_cleanup(data));
	data->sem_stop = sem_open(SEM_NAME_STOP, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (data->sem_stop == SEM_FAILED)
		return (sem_error_cleanup(data));
	return (true);
}

static t_philo	**init_philo(t_data *data)
{
	t_philo	**philos;
	size_t	index;

	if (!set(&philos, malloc(sizeof(t_philo *) * (data->nb_of_philos + 1))))
		return (null_error_msg(MALLOC_ERROR));
	memset(philos, 0, sizeof(t_philo *) * (data->nb_of_philos + 1));
	index = 0;
	while (index < data->nb_of_philos)
	{
		if (!set(&philos[index], malloc(sizeof(t_philo))))
			return (null_error_msg(MALLOC_ERROR));
		memset(philos[index], 0, sizeof(t_philo));
		philos[index]->data = data;
		philos[index]->id = index + 1;
		philos[index]->last_meal_time = 0;
		philos[index]->nb_meal_eat = 0;
		if (!set_names(philos[index]))
			return (null_error_msg(MALLOC_ERROR));
		index++;
	}
	return (philos);
}

t_data	*init_data(char **av)
{
	t_data	*data;

	if (!set(&data, malloc(sizeof(t_data))))
		return (null_error_msg(MALLOC_ERROR));
	memset(data, 0, sizeof(t_data));
	fill_data(data, av);
	if (!init_sem(data))
		return (NULL);
	if (!set(&data->philos, init_philo(data)))
		return (NULL);
	if (!set(&data->pids,
			malloc(sizeof * data->pids * data->nb_of_philos)))
		return (null_error_msg(MALLOC_ERROR));
	memset(data->pids, 0, sizeof * data->pids * data->nb_of_philos);
	data->ate_enought_monitor = 0;
	data->death_monitor = 0;
	data->sim_status = false;
	data->philo_full_count = 0;
	return (data);
}
