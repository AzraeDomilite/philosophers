/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:49:33 by blucken           #+#    #+#             */
/*   Updated: 2025/02/09 13:28:32 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*set(void *vtarget, void *void_new)
{
	void	**target;

	target = (void **) vtarget;
	*target = void_new;
	return (void_new);
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
