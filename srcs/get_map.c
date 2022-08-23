/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:42:33 by gudias            #+#    #+#             */
/*   Updated: 2022/08/23 14:18:47 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//will move in check_map.c
static int	check_extension(char *mapname)
{
	int	len;

	len = ft_strlen(mapname);
	if (ft_strncmp(mapname + (len - 4), ".cub", 4) != 0)
		return (error_msg("Invalid map extension, must be .cub"));
	return (0);
}

static int	open_map(char *mapname)
{
	int		fd;
	char	*path;

	path = ft_strjoin(MAPSDIR, mapname);
	fd = open(path, O_RDONLY);
	free(path);
	return (fd);
}

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
		
	   checks will be called HERE

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
