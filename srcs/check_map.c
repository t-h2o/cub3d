/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:40:48 by gudias            #+#    #+#             */
/*   Updated: 2022/08/25 18:32:29 by gudias           ###   ########.fr       */
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

int	check_charset(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S'
			&& c != 'E' && c != 'W' && c != ' ')
		return (error_msg("Invalid character in map"));
	return (0);
}

int	check_line_data(t_game *game, char *line)
{
	while (*line && *line != '\n')
	{
		if (check_charset(*line))
			return (error_msg("Invalid character in map"));
		if ((*line == 'N' || *line == 'S' || *line == 'E'
				|| *line == 'W') && game->player.x != -1)
			return (error_msg("More than 1 player"));
		line++;
	}
	return (0);
}

/*
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
				|| line[i] == 'W')
		{
			game->player.x = i;
			game->player.y = game->map_h;
			game->player.dir = line[i];
		}
		i++;
	}

		if (check_side_borders(line))
			exit_error("Both sides of the map should be walls");
		if (check_line_data(game, line))
			return ;
		save_line_data(game, line);
		line = get_next_line(fd);
	}
	if (check_walls(game->map[game->map_h - 1]))
		exit_error("Last line should be walls only");
}*/
