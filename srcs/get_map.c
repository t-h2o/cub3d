/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:42:33 by gudias            #+#    #+#             */
/*   Updated: 2022/08/21 15:13:23 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	open_map(char *mapname)
{
	int	fd;
	char	*path;

	path = ft_strjoin(MAPSDIR, mapname);
	fd = open(path, O_RDONLY);
	free(path);
	return (fd);
}

static void	save_line_data(t_game *game, char *line)
{
	int	i;
	char	**tmp;

	i = 0;
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
	game->map_h++;
	tmp = game->map;
	game->map = malloc(sizeof (char *) * (game->map_h + 1));
	if (!game->map)
		exit_error("Malloc :x");
	i = 0;
	if (tmp)
	{
		while (i < game->map_h - 1)
		{
			game->map[i] = tmp[i];
			i++;
		}
		free(tmp);
	}
	game->map[i] = line;
	game->map[i + 1] = NULL;
}

static void	read_map(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		exit_error("Map is empty!");
	if (check_walls(line))
		exit_error("First line should be walls only");
	save_line_data(game, line);
	line = get_next_line(fd);
	while (line)
	{
		if (check_side_borders(line))
			exit_error("Both sides of the map should be walls");
		if (check_line_data(game, line))
			return ;
		save_line_data(game, line);
		line = get_next_line(fd);
	}
	if (check_walls(game->map[game->map_h - 1]))
		exit_error("Last line should be walls only");
}

void	get_map(t_game *game, char *mapname)
{
	int	fd;

	if (check_extension(mapname))
		exit_error("Invalid map extension, must be .cub");
	fd = open_map(mapname);
	if (fd <= 0)
		exit_error("Couldn't find map in "MAPSDIR);
	read_map(game, fd);
	close(fd);
}
