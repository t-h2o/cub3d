/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:40:48 by gudias            #+#    #+#             */
/*   Updated: 2022/09/07 21:47:53 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	save_player_info(t_info *info, int x, int y)
{
	if (info->player.x != -1.0f)
		return (error_msg("More than 1 player"));
	else
	{
		info->player.x = (float) x + 0.5f;
		info->player.y = (float) y + 0.5f;
		if (info->map[y][x] == 'N')
			info->player.angle = 0.0f;
		else if (info->map[y][x] == 'S')
			info->player.angle = M_PI;
		else if (info->map[y][x] == 'E')
			info->player.angle = M_PI / 2;
		else if (info->map[y][x] == 'W')
			info->player.angle = (3 * M_PI) / 2;
		info->map[y][x] = '0';
		angle_delta(info->player.angle, info->player.delta);
	}
	return (0);
}

static int	check_charset(t_info *info, int y)
{
	char	data;
	int		x;

	x = -1;
	while (info->map[y][++x] && info->map[y][x] != '\n')
	{	
		data = info->map[y][x];
		if (data != '0' && data != '1')
		{
			if (data != 'N' && data != 'S' && data != 'E'
				&& data != 'W' && data != ' ')
				return (error_msg("Invalid character in map"));
			else if (data != ' ' && save_player_info(info, x, y))
				return (1);
		}
	}
	return (0);
}

static int	check_borders(t_info *info, int y)
{
	int	x;

	x = -1;
	while (info->map[y][++x] && info->map[y][x] != '\n')
	{	
		if (info->map[y][x] == '0')
		{
			if ((x == 0) || (y == info->map_h - 1)
				|| (x > 0 && info->map[y][x - 1] == ' ') ||
				(info->map[y][x + 1] != '0' && info->map[y][x + 1] != '1') ||
				(y > 0 && (int) ft_strlen(info->map[y - 1]) > x
				&& info->map[y - 1][x] == ' ') ||
				(y > 0 && (int) ft_strlen(info->map[y - 1]) <= x) ||
				(y < info->map_h && (int) ft_strlen(info->map[y + 1]) > x
				&& info->map[y + 1][x] == ' ') ||
				(y < info->map_h && (int) ft_strlen(info->map[y + 1]) <= x))
				return (error_msg("Map isn't closed by walls"));
		}
	}
	return (0);
}

int	check_map_data(t_info *info)
{
	int	y;

	if (!info->map)
		return (error_msg("Map is empty!"));
	y = -1;
	while (info->map[++y])
	{
		if (check_charset(info, y) || check_borders(info, y))
			return (1);
	}
	if (info->player.x == -1.0f)
		return (error_msg("No player in the map"));
	return (0);
}

int	check_extension(char *mapname)
{
	int	len;

	len = ft_strlen(mapname);
	if (ft_strncmp(mapname + (len - 4), ".cub", 4) != 0)
		return (error_msg("Invalid map extension, must be .cub"));
	return (0);
}
