/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:21:52 by gudias            #+#    #+#             */
/*   Updated: 2022/11/10 18:54:42 by gudias           ###   ########.fr       */
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

void	draw_door(t_info *info, int column, int door_height, int door_offset)
{
	char			*dst;
	float			x_scale;
	int				line;
	t_door			*door;
	unsigned int	px;

	dst = info->screen.addr + (column * info->screen.bpp / 8);
	if (door_offset > 0)
		dst += (door_offset * info->screen.line_len);
	x_scale = calc_x_scaling(&(info->ray[column]), 1);
	line = -1;
	if (door_offset < 0)
		line = -door_offset - 1;
	door = find_door(info, info->ray[column].door_hit);
	while (++line < door_height && (line + door_offset) < W_HEIGHT)
	{
		px = get_tx_pixel(&(info->texture[D + door->frame].img),
				x_scale, (float)line / door_height);
		if (px != 0xFF000000)
		{
			*(unsigned int *)dst = px;
			add_shade(dst, info->ray[column].door_dist);
		}
		dst += info->screen.line_len;
	}
}
