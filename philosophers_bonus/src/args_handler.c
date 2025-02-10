/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:46:53 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 11:47:03 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

bool	arg_valid(int ac, char **av)
{
	int	index;
	int	arg;

	index = 2;
	if (ft_atoi(av[1]) < 1)
		return (false);
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
