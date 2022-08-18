/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:42:33 by gudias            #+#    #+#             */
/*   Updated: 2022/08/18 17:20:28 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_extension(char *mapname)
{
	int	len;

	len = ft_strlen(mapname);
	if (ft_strncmp(mapname + (len - 4), ".cub", 4) != 0)
		return (1);
	return (0);
}

static int	open_map(char *mapname)
{
	int	fd;
	char	*path;

	path = ft_strjoin(MAPSDIR, mapname);
	fd = open(path, O_RDONLY);
	free(path);
	return (fd);
}

static char	**read_map(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		ft_printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	return ((char**)1);
}

char	**get_map(char *mapname)
{
	int	fd;
	char	**map;

	if (check_extension(mapname))
	{
		ft_printf("invalid map extension, must be .cub\n");
		return (NULL);
	}
	fd = open_map(mapname);
	if (fd <= 0)
	{
		ft_printf("couldn't find map in %s\n", MAPSDIR);
		return (NULL);
	}
	map = read_map(fd);
	return (map);
}
