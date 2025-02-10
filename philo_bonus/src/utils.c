/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blucken <blucken@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:00:14 by blucken           #+#    #+#             */
/*   Updated: 2025/02/10 13:00:17 by blucken          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		s++;
		count++;
	}
	return (count);
}

char	*ft_strcat(char	*dst, const char *src)
{
	size_t	i;
	size_t	j;

	if (!dst || !src)
		return (dst);
	i = 0;
	while (dst[i])
		i++;
	j = 0;
	while (src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}

char	*ft_utoa(unsigned int nb, size_t len)
{
	char	*ret;

	ret = malloc(sizeof * ret * (len + 1));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	len--;
	while (nb % 10)
	{
		ret[len--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (ret);
}

void	*set(void *vtarget, void *void_new)
{
	void	**target;

	target = (void **) vtarget;
	*target = void_new;
	return (void_new);
}
