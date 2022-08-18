/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:41:55 by gudias            #+#    #+#             */
/*   Updated: 2021/10/27 13:58:18 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_totrim(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *str, char const *set)
{
	char	*res;
	int		len;

	if (!str || !set)
		return (NULL);
	while (is_totrim(*str, set))
		str++;
	if (*str == '\0')
		len = 0;
	else
	{
		len = ft_strlen(str);
		while (is_totrim(str[len - 1], set))
			len--;
	}
	res = malloc(sizeof (char) * (len + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, str, len + 1);
	return (res);
}
