/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_monitor_sem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:41:25 by blucken           #+#    #+#             */
/*   Updated: 2025/02/11 13:50:08 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	init_semaphores(void)
{
	sem_unlink(SEM_NAME_FULL);
	sem_unlink(SEM_NAME_DEAD);
	sem_unlink(SEM_NAME_FORKS);
	sem_unlink(SEM_NAME_WRITE);
	sem_unlink(SEM_NAME_STOP);
}

static bool	open_sem(t_philo *philo)
{
	philo->sem_forks = sem_open(SEM_NAME_FORKS, O_CREAT,
			S_IRUSR | S_IWUSR, philo->data->nb_of_philos);
	if (philo->sem_forks == SEM_FAILED)
		return (false);
	philo->sem_philo_dead = sem_open(SEM_NAME_DEAD, O_CREAT,
			S_IRUSR | S_IWUSR, philo->data->nb_of_philos);
	if (philo->sem_philo_dead == SEM_FAILED)
		return (false);
	philo->sem_philo_full = sem_open(SEM_NAME_FULL, O_CREAT,
			S_IRUSR | S_IWUSR, philo->data->nb_of_philos);
	if (philo->sem_philo_full == SEM_FAILED)
		return (false);
	philo->sem_write = sem_open(SEM_NAME_WRITE, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (philo->sem_write == SEM_FAILED)
		return (false);
	philo->sem_meal = sem_open(philo->sem_meal_name, O_CREAT,
			S_IRUSR | S_IWUSR, 1);
	if (philo->sem_meal == SEM_FAILED)
		return (false);
	sem_unlink(philo->sem_meal_name);
	return (true);
}

void	init_monitor_sem(t_data *data, t_philo *philo)
{
	if (data->nb_of_philos == 1)
		return ;
	sem_unlink(philo->sem_meal_name);
	if (!open_sem(philo))
	{
		sem_error_cleanup(data);
		child_exit(data, CHILD_EXIT_SEM_ERROR);
	}
	memset(&philo->monitor, 0, sizeof(pthread_t));
	if (pthread_create(&philo->monitor, NULL, &philo_monitor, data))
	{
		sem_error_cleanup(data);
		child_exit(data, CHILD_EXIT_PTHREAD_ERROR);
	}
	return ;
}
