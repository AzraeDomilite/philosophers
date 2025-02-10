/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:41:09 by blucken           #+#    #+#             */
/*   Updated: 2025/02/09 19:55:09 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac < 5 || ac > 6)
		return (error_msg(USAGE_MSG, EXIT_FAILURE));
	if (!arg_valid(ac, av))
		return (error_msg(NON_VALID_ARGS, EXIT_FAILURE));
	if (!set(&data, init_data(av)))
		return (error_msg(INIT_ERROR, EXIT_FAILURE));
	if (!start_philo(data))
		return (error_msg(START_ERROR_MSG, EXIT_FAILURE));
	if (stop_philo(data) == -1)
		return (free_data(data), error_msg(STOP_ERROR_MSG, EXIT_FAILURE));
	return (free_data(data), EXIT_SUCCESS);
	return (0);
}
