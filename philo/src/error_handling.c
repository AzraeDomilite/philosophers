/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 11:49:22 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 11:49:22 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief take the message and the exit number
 * 
 * @param str 
 * @param exit_nb 
 * @return int 
 */
int	error_msg(char *str, int exit_nb)
{
	printf("%s\n", str);
	return (exit_nb);
}

/**
 * @brief take the error msg and return NULL *str
 * 
 * @param str 
 * @return void* 
 */
void	*null_error_msg(char *str)
{
	printf("%s\n", str);
	return (NULL);
}
