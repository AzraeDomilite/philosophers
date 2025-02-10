/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:18:21 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 12:18:44 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static pthread_mutex_t	*init_forks(t_data *data)
{
	pthread_mutex_t	*forks;
	size_t			index;

	forks = malloc(sizeof(pthread_mutex_t) * data->nb_of_philos);
	if (!forks)
		return (null_error_msg(MALLOC_ERROR));
	index = 0;
	while (index < data->nb_of_philos)
	{
		if (pthread_mutex_init(&forks[index], 0) != 0)
			return (null_error_msg(MUTEX_ERROR));
		index++;
	}
	return (forks);
}

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

static bool	init_mutex(t_data *data)
{
	if (!set(&data->fork_locks, init_forks(data)))
		return (false);
	if (pthread_mutex_init(&data->sim_status_lock, 0))
		return (free_data(data), error_msg(MUTEX_ERROR, false));
	if (pthread_mutex_init(&data->print_lock, 0))
		return (free_data(data), error_msg(MUTEX_ERROR, false));
	return (true);
}

t_data	*init_data(char **av)
{
	t_data	*data;

	if (!set(&data, malloc(sizeof(t_data))))
		return (null_error_msg(MALLOC_ERROR));
	memset(data, 0, sizeof(t_data));
	fill_data(data, av);
	if (!set(&data->philos, init_philo(data)))
		return (NULL);
	if (!init_mutex(data))
		return (NULL);
	if (DEBUG_MODE)
		print_data(data);
	return (data);
}
