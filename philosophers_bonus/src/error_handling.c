/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:48:03 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 11:48:04 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	child_exit(t_data *data, int exit_code)
{
	sem_post(data->current_philo->sem_meal);
	pthread_join(data->current_philo->monitor, NULL);
	if (exit_code == CHILD_EXIT_SEM_ERROR)
		error_msg(SEM_ERROR, EXIT_FAILURE);
	if (exit_code == CHILD_EXIT_PTHREAD_ERROR)
		error_msg(THREAD_ERROR, EXIT_FAILURE);
	sem_close(data->current_philo->sem_forks);
	sem_close(data->current_philo->sem_philo_full);
	sem_close(data->current_philo->sem_philo_dead);
	sem_close(data->current_philo->sem_write);
	sem_close(data->current_philo->sem_meal);
	free_data(data);
	exit(exit_code);
}

int	error_failure(char *str, t_data *data)
{
	if (data != NULL)
		free_data(data);
	return (error_msg(str, EXIT_FAILURE));
}

int	error_msg(char *str, int exit_nb)
{
	printf("%s\n", str);
	return (exit_nb);
}

void	*null_error_msg(char *str)
{
	printf("%s\n", str);
	return (NULL);
}
