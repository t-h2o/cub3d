/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:40:48 by gudias            #+#    #+#             */
/*   Updated: 2022/08/29 16:53:47 by gudias           ###   ########.fr       */
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

static int	check_charset(t_info *info, int x, int y)
{
	char	data;

	data = info->map[y][x];
	if (data != '0' && data != '1')
	{
		if (data != 'N' && data != 'S' && data != 'E'
				&& data != 'W' && data != ' ')
			return (error_msg("Invalid character in map"));
		else if (data != ' ')
		{
			if (info->player.x != -1.0f)
				return (error_msg("More than 1 player"));
			else
			{
				info->player.x = (float) x;
				info->player.y = (float) y;
				//info->player.dir = info->map[y][x];
			}	
		}
	}
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
			if (check_charset(info, x, y))
				return (1);

		}
	}
	if (info->player.x == -1.0f)
		return (error_msg("No player in map"));

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

/*
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
