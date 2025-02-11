/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_names.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:12:53 by blucken           #+#    #+#             */
/*   Updated: 2025/02/11 13:27:11 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static char	*set_sem_name(t_philo *philo)
{
	char	*name;
	char	*id;
	size_t	len;

	len = ft_strlen("philo_bonus_");
	id = ft_utoa(philo->id, 10);
	if (!id)
		return (NULL);
	name = malloc(sizeof(char) * (len + ft_strlen(id) + 1));
	if (!name)
	{
		free(id);
		return (NULL);
	}
	memset(name, 0, len + ft_strlen(id) + 1);
	ft_strcat(name, "philo_bonus_");
	ft_strcat(name, id);
	free(id);
	return (name);
}

bool	set_names(t_philo *philo)
{
	philo->sem_meal_name = set_sem_name(philo);
	if (philo->sem_meal_name == NULL)
		return (false);
	return (true);
}
