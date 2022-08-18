/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:32:01 by gudias            #+#    #+#             */
/*   Updated: 2021/10/27 13:57:29 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	total_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1) + 1;
	total_len = s1_len + ft_strlen(s2);
	res = malloc (sizeof(char) * total_len);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, s1_len);
	ft_strlcat(res, s2, total_len);
	return (res);
}
/* SOL2
//	size_t	i;
	i = 0;
	while (i < (s1_len - 1))
	{
		res[i] = s1[i];
		i++;
	}
	while (i < (total_len - 1))
	{
		res[i] = s2[i - (s1_len - 1)];
		i++;
	}
	res[i] = '\0';
*/
