/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:17:13 by blucken           #+#    #+#             */
/*   Updated: 2025/02/09 18:35:50 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	print_status(t_philo *philo, char *str, char *color)
{
	if (COLOR_MODE)
		printf("%6ld %3d %s%s\n\e[0m", get_time() - philo->data->start_timer,
			philo->id + 1, color, str);
	else
		printf("%ld %d %s\n", get_time() - philo->data->start_timer,
			philo->id + 1, str);
}

void	print_output(t_philo *philo, bool monitor, t_status status)
{
	sem_wait(philo->sem_write);
	if (status == DIE)
		print_status(philo, "died", RED);
	else if (status == EAT)
		print_status(philo, "is eating", PURPLE);
	else if (status == SLEEP)
		print_status(philo, "is sleeping", CYAN);
	else if (status == THINK)
		print_status(philo, "is thinking", GREEN);
	else if (status == FORK_1 || status == FORK_2)
		print_status(philo, "has taken a fork", ORANGE);
	if (!monitor)
		sem_post(philo->sem_write);
}
