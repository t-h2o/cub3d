/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:10:12 by gudias            #+#    #+#             */
/*   Updated: 2021/10/22 17:39:46 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *tofind, size_t len)
{
	size_t	i;
	size_t	j;

	if (*tofind == '\0')
		return ((char *)str);
	i = 0;
	while (i < len && str[i] != '\0')
	{	
		j = 0;
		while (i + j < len && str[i + j] == tofind[j])
		{
			j++;
			if (tofind[j] == '\0')
				return ((char *)str + i);
		}
		i++;
	}
	return (NULL);
}
