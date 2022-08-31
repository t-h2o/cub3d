/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:42:33 by gudias            #+#    #+#             */
/*   Updated: 2022/08/31 19:41:24 by gudias           ###   ########.fr       */
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

static int	save_map_data(t_info *info, char *line)
{
	int		i;
	char	**tmp;
	
	info->map_h++;
	tmp = info->map;
	info->map = malloc(sizeof (char *) * (info->map_h + 1));
	if (!info->map)
		return (error_msg("Malloc :x"));
	i = 0;
	if (tmp)
	{
		while (i < info->map_h - 1)
		{
			info->map[i] = tmp[i];
			i++;
		}
		free(tmp);
	}
	info->map[i] = line;
	info->map[i + 1] = NULL;
	return (0);
}

static int	save_map_info(t_info *info, char *line)
{
	char	*str;
	int	ret;

	ret = 0;
	str = skip_whitespaces(line);
	if (str)
	{
		if (ft_strncmp(str, "NO", 2) == 0)
			info->texture.north = skip_whitespaces(str + 2);
		else if (ft_strncmp(str, "SO", 2) == 0)
			info->texture.south = skip_whitespaces(str + 2);
		else if (ft_strncmp(str, "EA", 2) == 0)
			info->texture.east = skip_whitespaces(str + 2);
		else if (ft_strncmp(str, "WE", 2) == 0)
			info->texture.west = skip_whitespaces(str + 2);
		else if (*str == 'F')
			info->texture.floor = skip_whitespaces(str + 1);
		else if (*str == 'C')
			info->texture.ceil = skip_whitespaces(str + 1);
		else
			ret = 1;
		free(str);
	}
	return (ret);
}

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
	{
		free_map(info->map);
		return (1);
	}
	return (0);
}
