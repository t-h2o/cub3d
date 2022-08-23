/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:42:33 by gudias            #+#    #+#             */
/*   Updated: 2022/08/23 13:57:17 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	open_map(char *mapname)
{
	int		fd;
	char	*path;

	path = ft_strjoin(MAPSDIR, mapname);
	fd = open(path, O_RDONLY);
	free(path);
	return (fd);
}

/*static void	save_line_data(t_game *game, char *line)
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
}*/

static int	save_line(t_game *game, char *line)
{
	int		i;
	char	**tmp;

	game->map_h++;
	tmp = game->map;
	game->map = malloc(sizeof (char *) * (game->map_h + 1));
	if (!game->map)
		return (error_msg("Malloc :x"));
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
	return (0);
}

static int	is_map_valid(t_game *game)
{
	if (!game->map)
		return(error_msg("Map is empty!"));
	/* WIPP
	if (check_walls(line))
		exit_error("First line should be walls only");
	if (check_side_borders(line))
		exit_error("Both sides of the map should be walls");
	if (check_line_data(game, line))
		return ;
	if (check_walls(game->map[game->map_h - 1]))
		exit_error("Last line should be walls only");
	*/
	return (0);
}

static void read_map(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (save_line(game, line))
		{
			free(line);
			return ;
		}
		line = get_next_line(fd);
	}
}

int	get_map(t_game *game, char *mapname)
{
	int	fd;

	if (check_extension(mapname))
		return (1);
	fd = open_map(mapname);
	if (fd <= 0)
		return(error_msg("Couldn't find map in "MAPSDIR));
	read_map(game, fd);
	close(fd);
	if (is_map_valid(game))
	{
		free(game->map);
		return (1);
	}
	return (0);
}
