/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:18:15 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 12:18:18 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file main.c
 * @author blucken
 * @brief start function only
 * @version 0.1
 * @date 2025-02-06
 * 
 */

#include "../includes/philo.h"

/**
 * @brief start function
 * check the args, fill the data struct then start the simulation
 * finaly stop it and exit.
 * all error is handle whith a msg (define in header)
 * @param ac should be 5 or 6
 * @param av Usage </philo <number_of_philosophers>
 * <time_to_die> <time_to_eat> <time_to_sleep>
 * [number_of_times_each_philosopher_must_eat] (optional)
 * 
 * @return int 
 */
int	main(int ac, char **av)
{
	t_data	*data;

	data = NULL;
	if (ac < 5 || ac > 6)
		return (error_msg(USAGE_MSG, EXIT_FAILURE));
	if (!arg_valid(ac, av))
		return (error_msg(NON_VALID_ARGS, EXIT_FAILURE));
	if (!set(&data, init_data(av)))
		return (free_data(data), error_msg(INIT_ERROR, EXIT_FAILURE));
	if (!start_philo(data))
		error_msg(START_ERROR_MSG, EXIT_FAILURE);
	stop_philo(data);
	return (EXIT_SUCCESS);
}
