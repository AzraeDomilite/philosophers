/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:40:16 by blucken           #+#    #+#             */
/*   Updated: 2025/02/11 15:41:11 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	take_fork(t_philo *philo)
{
	sem_wait(philo->sem_forks);
	sem_wait(philo->sem_meal);
	if (philo->nb_forks_held <= 0)
		print_output(philo, false, FORK_1);
	if (philo->nb_forks_held == 1)
		print_output(philo, false, FORK_2);
	philo->nb_forks_held += 1;
	sem_post(philo->sem_meal);
}

static void	philo_think(t_philo *philo, bool first)
{
	time_t	time_to_think;

	sem_wait(philo->sem_meal);
	time_to_think = (philo->data->time_to_die
			- (get_time() - philo->last_meal_time)
			- philo->data->time_to_eat) / 2;
	sem_post(philo->sem_meal);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && first == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	print_output(philo, false, THINK);
	philo_sleep(time_to_think);
}

void	philo_eat_sleep(t_philo *philo)
{
	take_fork(philo);
	take_fork(philo);
	print_output(philo, false, EAT);
	sem_wait(philo->sem_meal);
	philo->last_meal_time = get_time();
	sem_post(philo->sem_meal);
	philo_sleep(philo->data->time_to_eat);
	print_output(philo, false, SLEEP);
	sem_post(philo->sem_forks);
	sem_post(philo->sem_forks);
	sem_wait(philo->sem_meal);
	philo->nb_forks_held -= 2;
	philo->nb_meal_eat += 1;
	sem_post(philo->sem_meal);
	philo_sleep(philo->data->time_to_sleep);
}

static void	philo_routine(t_philo *philo)
{
	if (philo->id % 2)
		philo_think(philo, true);
	while (1)
	{
		philo_eat_sleep(philo);
		philo_think(philo, false);
	}
}

void	philo(t_data *data)
{
	t_philo	*philo;

	philo = data->current_philo;
	if (philo->data->nb_of_philos == 1)
		one_philo(philo);
	init_monitor_sem(data, philo);
	if (!philo->data->nb_time_ph_must_eat)
	{
		sem_post(philo->sem_philo_full);
		child_exit(data, CHILD_EXIT_FULL);
	}
	if (!philo->data->time_to_die)
	{
		sem_post(philo->sem_philo_full);
		child_exit(data, CHILD_EXIT_DEAD);
	}
	sem_wait(philo->sem_meal);
	philo->last_meal_time = philo->data->start_timer;
	sem_post(philo->sem_meal);
	start_delay(philo->data->start_timer);
	philo_routine(philo);
}
