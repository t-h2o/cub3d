/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:40:48 by gudias            #+#    #+#             */
/*   Updated: 2022/08/20 17:26:37 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *mapname)
{
	int	len;

	len = ft_strlen(mapname);
	if (ft_strncmp(mapname + (len - 4), ".cub", 4) != 0)
		return (1);
	return (0);
}

int	check_walls(char *line)
{
	while (*line && *line != '\n')
	{
		if (*line != '1' && *line != ' ')
			return (1);
		line++;
	}
	return (0);
}

int	check_side_borders(char *line)
{
	while (*line && *line == ' ')
		line++;
	if (line[0] != '1' || line[ft_strlen(line) - 2] != '1')
		return (1);
	while (*line)
	{
		if (*line == ' ' && *(line - 1) != '1' && *(line - 1) != ' '
				&& *(line + 1) != '1' && *(line + 1) != ' ')
			return (1);
		line++;
	}
	return (0);
}

int	check_charset(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S'
			&& c != 'E' && c != 'W' && c != ' ')
		return (1);
	return (0);
}

int	check_line_data(t_game *game, char *line)
{
	while (*line && *line != '\n')
	{
		if (check_charset(*line))
		{
			ft_printf("Error\nInvalid character in map\n");
			return (1);
		}
		if ((*line == 'N' || *line == 'S' || *line == 'E'
				|| *line == 'W') && game->player.x != -1)
		{
			ft_printf("Error\nMore than 1 player\n");
			return (1);
		}
		line++;
	}
	return (0);
}
