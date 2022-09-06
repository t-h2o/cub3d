/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:30:28 by gudias            #+#    #+#             */
/*   Updated: 2022/09/04 21:28:38 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

static int	ft_atoi_pos(char *str)
{
	unsigned int	num;

	while (is_whitespace(*str))
		str++;
	num = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (-1);
		num = (num * 10) + *str - '0';
		if (num > 255)
			return (-1);
		str++;
	}
	return (num);
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

int	convert_rgb(char *rgb)
{
	char	**splitted;
	int		r;
	int		g;
	int		b;

	splitted = ft_split(rgb, ',');
	if (!splitted || !splitted[0] || !splitted[1]
		|| !splitted[2] || splitted[3])
	{
		free_array(splitted);
		return (-1);
	}
	r = ft_atoi_pos(splitted[0]);
	g = ft_atoi_pos(splitted[1]);
	b = ft_atoi_pos(splitted[2]);
	if (r == -1 || g == -1 || b == -1)
	{
		free_array(splitted);
		return (-1);
	}
	free_array(splitted);
	return (r << 16 | g << 8 | b);
}
