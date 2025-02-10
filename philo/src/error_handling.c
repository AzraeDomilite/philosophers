/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:34:01 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 14:34:03 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Prints error message and returns exit code
 * 
 * @param str Error message to display
 * @param exit_nb Exit code to return
 * @return int The provided exit code
 * 
 * Used for general error handling with custom messages
 */
int	error_msg(char *str, int exit_nb)
{
	printf("%s\n", str);
	return (exit_nb);
}

/**
 * @brief Prints error message and returns NULL
 * 
 * @param str Error message to display
 * @return void* Always returns NULL
 * 
 * Specialized for functions that return pointers
 */
void	*null_error_msg(char *str)
{
	printf("%s\n", str);
	return (NULL);
}
