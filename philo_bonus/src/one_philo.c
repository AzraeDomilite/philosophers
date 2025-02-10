/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 20:00:27 by blucken           #+#    #+#             */
/*   Updated: 2025/02/09 20:00:27 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	one_philo(t_philo *philo)
{
	philo->sem_philo_full = sem_open(SEM_NAME_FULL, O_CREAT,
			S_IRUSR | S_IWUSR, philo->data->nb_of_philos);
	if (philo->sem_philo_full == SEM_FAILED)
		exit(CHILD_EXIT_SEM_ERROR);
	sem_wait(philo->sem_philo_full);
	start_delay(philo->data->start_timer);
	if (philo->data->nb_time_ph_must_eat == 0)
	{
		sem_post(philo->sem_philo_full);
		exit(CHILD_EXIT_FULL);
	}
	print_status(philo, "has taken a fork", ORANGE);
	philo_sleep(philo->data->time_to_die);
	print_status(philo, "died", RED);
	free_data(philo->data);
	exit(CHILD_EXIT_DEAD);
}
