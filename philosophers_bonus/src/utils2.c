/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:55:51 by blucken           #+#    #+#             */
/*   Updated: 2025/02/09 18:56:26 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	unlink_sems(void)
{
	sem_unlink(SEM_NAME_FORKS);
	sem_unlink(SEM_NAME_WRITE);
	sem_unlink(SEM_NAME_FULL);
	sem_unlink(SEM_NAME_DEAD);
	sem_unlink(SEM_NAME_STOP);
}

static bool	ft_isdigit(char c)
{
	if (c < '0' || c > '9')
		return (false);
	return (true);
}

bool	ft_is_str_digit(char *str)
{
	while (str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

static int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	else if (c >= '\t' && c <= '\r')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	n;

	while (ft_isspace(*nptr))
		nptr++;
	sign = 1;
	if (*nptr == '-' || *nptr == '+')
		sign = 1 + '+' - (*(nptr++));
	n = 0;
	while (ft_isdigit(*nptr))
	{
		n = n * 10 + (*nptr - '0');
		nptr++;
	}
	return (n * sign);
}
