/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:29:32 by gudias            #+#    #+#             */
/*   Updated: 2021/10/27 12:47:56 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != c) && ((i == 0) || (str[i - 1] == c)))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *str, char c)
{
	char	**res;
	int		i;
	int		j;
	int		start;

	if (!str)
		return (NULL);
	res = malloc (sizeof (char *) * (count_words(str, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	start = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != c) && (i == 0 || (str[i - 1] == c)))
			start = i;
		if ((str[i] != c) && ((str[i + 1] == '\0') || (str[i + 1] == c)))
			res[j++] = ft_substr(str, start, (i - start) + 1);
		i++;
	}
	res[j] = 0;
	return (res);
}
