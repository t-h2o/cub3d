/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:30:28 by gudias            #+#    #+#             */
/*   Updated: 2022/08/29 15:14:57 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v'
			|| c == '\f'|| c == '\r')
		return (1);
	else
		return (0);
}

char	*skip_whitespaces(char *line)
{
	char	*str;
	char	*end;

	while (is_whitespace(*line))
		line++;
	if (*line == '\0')
		return (NULL);
	end = line + ft_strlen(line) - 1;
	while (is_whitespace(*end))
			end--;
	if (line == end)
		return (NULL);
	str = ft_substr(line, 0, end - line + 1);
	return (str);
}
