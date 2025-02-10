/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:46:47 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 14:40:45 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Validates command line arguments
 * 
 * @param ac Argument count
 * @param av Argument array
 * @return true If all arguments are valid
 * @return false If any argument is invalid
 * 
 * Checks:
 * - All arguments are digits
 * - Number of philosophers doesn't exceed MAX_PHILOS
 * - No negative values
 * - Valid ranges for time values
 */
bool	arg_valid(int ac, char **av)
{
	int	index;
	int	arg;

	index = 2;
	while (ac > index)
	{
		if (ft_is_str_digit(av[index]))
			return (error_msg(NON_DIGIT_ARGS, false));
		arg = ft_atoi(av[index]);
		if (index == 1 && arg > MAX_PHILOS)
			return (error_msg(PHILOS_MAX_REACH, false));
		if (arg < 0)
			return (error_msg(NO_NEG, false));
		index++;
	}
	return (true);
}
