/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 12:23:38 by gudias            #+#    #+#             */
/*   Updated: 2021/10/22 17:37:14 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	char	*newstring;
	int		i;

	if (!str || !f)
		return (NULL);
	newstring = ft_strdup(str);
	if (!newstring)
		return (NULL);
	i = 0;
	while (str[i])
	{
		newstring[i] = f(i, str[i]);
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}
