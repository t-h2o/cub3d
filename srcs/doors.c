/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:21:52 by gudias            #+#    #+#             */
/*   Updated: 2022/11/07 12:14:58 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Check doors error
//  not at map extremity
//  surrounded by wall (vertical or horizontal)
int	check_doors(t_info *info, int y)
{
	int	x;

	x = -1;
	while (info->map[y][++x] && info->map[y][x] != '\n')
	{
		if (info->map[y][x] == 'D')
		{
			if (x == 0 || x >= (int) ft_strlen(info->map[y]) - 2 || y == 0
				|| y == info->mapsize[Y] - 1 || (info->map[y][x + 1] == '0'
				&& (info->map[y][x - 1] != '0'
				|| info->map[y + 1][x] != '1' || info->map[y - 1][x] != '1'))
				|| (info->map[y][x + 1] == '1' && (info->map[y][x - 1] != '1'
				|| info->map[y + 1][x] != '0' || info->map[y - 1][x] != '0')))
				return (error_msg("Invalid door position"));
			add_door(info, x, y);
		}
	}
	return (0);
}

void	add_door(t_info *info, int x, int y)
{
	t_door	*new_door;

	new_door = malloc(sizeof (t_door));
	if (!new_door)
		return ;
	new_door->pos[X] = x;
	new_door->pos[Y] = y;
	new_door->frame = 0;
	new_door->opening = 0;
	new_door->closing = 0;
	new_door->next = info->doors;
	info->doors = new_door;
}

t_door	*find_door(t_info *info, float pos[2])
{
	t_door	*door;

	door = info->doors;
	while (door)
	{
		if (door->pos[X] == (int)pos[X] && door->pos[Y] == (int)pos[Y])
			return (door);
		door = door->next;
	}
	return (NULL);
}

int	load_doors(t_info *info)
{
	if (load_xpm_image(info, &(info->texture[D].img), TX_DOOR)
		|| load_xpm_image(info, &(info->texture[D2].img), TX_DOOR2)
		|| load_xpm_image(info, &(info->texture[D3].img), TX_DOOR3)
		|| load_xpm_image(info, &(info->texture[D4].img), TX_DOOR4)
		|| load_xpm_image(info, &(info->texture[D5].img), TX_DOOR5)
		|| load_xpm_image(info, &(info->texture[D6].img), TX_DOOR6)
		|| load_xpm_image(info, &(info->texture[D7].img), TX_DOOR7)
		|| load_xpm_image(info, &(info->texture[D8].img), TX_DOOR8)
		|| load_xpm_image(info, &(info->texture[D9].img), TX_DOOR9))
		return (1);
	return (0);
}
