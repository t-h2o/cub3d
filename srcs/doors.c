/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:21:52 by gudias            #+#    #+#             */
/*   Updated: 2022/10/07 20:24:40 by gudias           ###   ########.fr       */
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
			//add_door(info->doors, x, y)
		}
	}
	return (0);
}

/*
void	add_door(info->doors, pos[2])
{
	t_door	*ptr;
	t_door	*new_door;

	new_door = malloc...
	new_door.x = pos[X];
	new_door.y = pos[Y];
	new_door.open = 0;

	ptr = info->doors;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new_door;
}

t_door	*find_door(info->doors, pos[2])
{
	t_door	*door;

	door = info->doors;
	while (door)
	{
		if (door.pos == pos[2])
			return (door)
		door = door->next;
	}
	return (NULL);
}
*/
