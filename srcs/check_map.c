/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:40:48 by gudias            #+#    #+#             */
/*   Updated: 2022/08/30 18:10:29 by gudias           ###   ########.fr       */
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

// check the char set of the map
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
				if (data == 'N')
					info->player.direction = 0.0f;
				else if (data == 'S')
					info->player.direction = M_PI;
				else if (data == 'E')
					info->player.direction = M_PI / 2;
				else if (data == 'W')
					info->player.direction = (3 * M_PI) / 2;
				info->map[y][x] = '0';
			}	
		}
	}
	return (0);
}

// Iteration lines of the map
//   check each char in the line
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
		if (check_borders(info, y))
			return (1);
	}
	if (info->player.x == -1.0f)
		return (error_msg("No player in the map"));

	return (0);
}

// Check if the 1st and last line of the map has only 1 or spaces
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

int	check_borders(t_info *info, int y)
{
	int		x;

	x = 0;
	while (info->map[y][x] && info->map[y][x] != '\n')
	{
		if (info->map[y][x] == '0')
		{
			if ((x == 0) || (y == info->map_h - 1) ||
				(x > 0 && info->map[y][x - 1] == ' ') ||
				(info->map[y][x + 1] != '0' && info->map[y][x + 1] != '1') ||
				(y > 0 && (int) ft_strlen(info->map[y - 1]) > x && info->map[y - 1][x] == ' ') ||
				(y > 0 && (int) ft_strlen(info->map[y - 1]) <= x) ||
				(y < info->map_h && (int) ft_strlen(info->map[y + 1]) > x && info->map[y + 1][x] == ' ') ||
				(y < info->map_h && (int) ft_strlen(info->map[y + 1]) <= x))
				return (error_msg("Map isn't closed by walls"));
		}
		x++;
	}
	return (0);

