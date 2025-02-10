/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:49:33 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 14:34:01 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Sets a pointer value safely
 * 
 * @param vtarget Pointer to the target pointer
 * @param void_new New value to set
 * @return void* Returns the new value
 * 
 * Helper function for safe pointer assignment
 */
void	*set(void *vtarget, void *void_new)
{
	void	**target;

	target = (void **) vtarget;
	*target = void_new;
	return (void_new);
}

/**
 * @brief Checks if character is a digit
 * 
 * @param c Character to check
 * @return true If character is between '0' and '9'
 * @return false Otherwise
 */
static bool	ft_isdigit(char c)
{
	if (c < '0' || c > '9')
		return (false);
	return (true);
}

/**
 * @brief Validates if string contains only digits
 * 
 * @param str String to check
 * @return true If string contains only digits
 * @return false If string contains non-digits
 */
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

/**
 * @brief Checks if character is whitespace
 * 
 * @param c Character to check
 * @return int 1 if whitespace, 0 if not
 */
static int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	else if (c >= '\t' && c <= '\r')
		return (1);
	else
		return (0);
}

/**
 * @brief Converts string to integer
 * 
 * @param nptr String to convert
 * @return int Converted integer value
 * 
 * Handles:
 * - Leading whitespace
 * - Sign characters
 * - Multiple digits
 */
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
