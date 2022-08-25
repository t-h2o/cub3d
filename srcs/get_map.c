/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:42:33 by gudias            #+#    #+#             */
/*   Updated: 2022/08/25 18:27:49 by gudias           ###   ########.fr       */
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

static int	save_line(t_info *info, char *line)
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

static int	is_map_valid(t_info *info)
{
	if (!info->map)
		return (error_msg("Map is empty!"));
	/* WIP
		
	   checks will be called HERE

	*/
	return (0);
}

static void	read_map(t_info *info, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (save_line(info, line))
		{
			free(line);
			return ;
		}
		line = get_next_line(fd);
	}
	close(fd);
}

int	get_map(t_info *info, char *mapname)
{
	int	fd;

	if (check_extension(mapname))
		return (1);
	if (open_map(mapname, &fd))
		return (1);
	read_map(info, fd);
	if (is_map_valid(info))
	{
		free_map(info->map);
		return (1);
	}
	return (0);
}
