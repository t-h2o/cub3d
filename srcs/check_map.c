/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:40:48 by gudias            #+#    #+#             */
/*   Updated: 2022/08/27 19:11:15 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *mapname)
{
	int	len;

	len = ft_strlen(mapname);
	if (ft_strncmp(mapname + (len - 4), ".cub", 4) != 0)
		return (error_msg("Invalid map extension, must be .cub"));
	return (0);
}

static int	check_charset(char data)
{
	if (data != '0' && data != '1' && data != 'N' && data != 'S'
			&& data != 'E' && data != 'W' && data != ' ')
		return (1);
	return (0);
}

int	check_map_data(t_info *info)
{
	int	x;
	int	y;
	
	y = -1;
	while (info->map[++y])
	{
		x = -1;
		while (info->map[y][++x] && info->map[y][x] != '\n')
		{	
			if (check_charset(info->map[y][x]))
				return (error_msg("Invalid character in map"));
		}
	}
	return (0);
}

/*
int	check_walls(char *line)
{
	while (*line && *line != '\n')
	{
		if (*line != '1' && *line != ' ')
			return (error_msg("First & last line should be walls only"));
		line++;
	}
	return (0);
}

int	check_side_borders(char *line)
{
	while (*line && *line == ' ')
		line++;
	if (line[0] != '1' || line[ft_strlen(line) - 2] != '1')
		return (error_msg("Both sides of the map should be walls"));
	while (*line)
	{
		if (*line == ' ' && *(line - 1) != '1' && *(line - 1) != ' '
				&& *(line + 1) != '1' && *(line + 1) != ' ')
			return (error_msg("Both sides of the map should be walls"));
		line++;
	}
	return (0);
}

*/
