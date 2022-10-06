/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:42:33 by gudias            #+#    #+#             */
/*   Updated: 2022/10/06 14:07:45 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	open_map(char *mapname, int *fd)
{
	char	*path;

	path = ft_strjoin(MAPSDIR, mapname);
	*fd = open(path, O_RDONLY);
	free(path);
	if (*fd <= 0)
		return (error_msg("Couldn't find map in "MAPSDIR));
	return (0);
}

// Save the map into a double pointer
static int	save_map_data(t_info *info, char *line)
{
	int		i;
	int		len;
	char	**tmp;

	info->mapsize[Y]++;
	tmp = info->map;
	info->map = malloc(sizeof (char *) * (info->mapsize[Y] + 1));
	if (!info->map)
		return (error_msg("Malloc :x"));
	i = 0;
	if (tmp)
	{
		while (i < info->mapsize[Y] - 1)
		{
			info->map[i] = tmp[i];
			i++;
		}
		free(tmp);
	}
	info->map[i] = line;
	info->map[i + 1] = NULL;
	len = ft_strlen(line) - 1;
	if (len > info->mapsize[X])
		info->mapsize[X] = len;
	return (0);
}

// Read the texture path and the color of the floor and the ceilling
static int	save_map_info(t_info *info, char *line)
{
	char	*str;
	int		ret;

	ret = 0;
	str = skip_whitespaces(line);
	if (str)
	{
		if (ft_strncmp(str, "NO", 2) == 0)
			info->texture[NO].path = skip_whitespaces(str + 2);
		else if (ft_strncmp(str, "SO", 2) == 0)
			info->texture[SO].path = skip_whitespaces(str + 2);
		else if (ft_strncmp(str, "EA", 2) == 0)
			info->texture[EA].path = skip_whitespaces(str + 2);
		else if (ft_strncmp(str, "WE", 2) == 0)
			info->texture[WE].path = skip_whitespaces(str + 2);
		else if (*str == 'F')
			info->texture[FL].path = skip_whitespaces(str + 1);
		else if (*str == 'C')
			info->texture[CE].path = skip_whitespaces(str + 1);
		else
			ret = 1;
		free(str);
	}
	return (ret);
}

// 1. Get the optional informations
// 2. Get the map
static void	read_mapfile(t_info *info, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && !save_map_info(info, line))
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line && !save_map_data(info, line))
		line = get_next_line(fd);
	close(fd);
}

int	load_map(t_info *info, char *mapname)
{
	int	fd;

	if (check_extension(mapname))
		return (1);
	if (open_map(mapname, &fd))
		return (1);
	read_mapfile(info, fd);
	if (check_map_data(info))
		return (1);
	return (0);
}
