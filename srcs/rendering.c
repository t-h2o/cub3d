/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:50:53 by gudias            #+#    #+#             */
/*   Updated: 2022/09/21 23:55:30 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Draw a column of a wall in the screen
// - define the wall_height
// - define the wall_offset (start position)
// - get address of the first pixel
// - draw the pixel
// - increment by a line
// (instead of the color, we will have to define
// the pixel to draw based on a texture)
static void	draw_wall(t_info *info, int column, int color)
{
	int		wall_height;
	int		wall_offset;
	char	*dst;

	wall_height = W_HEIGHT / info->ray[column].distance;
	if (wall_height > W_HEIGHT)
		wall_height = W_HEIGHT;
	wall_offset = (W_HEIGHT / 2) - (wall_height >> 1);
	dst = info->screen.addr + (wall_offset * info->screen.line_length)
		+ (column * info->screen.bits_per_pixel / 8);
	while (wall_height--)
	{
		*(unsigned int *)dst = color;
		dst += info->screen.line_length;
	}
}

static void	clear_screen(t_info *info)
{
	ft_memset(info->screen.addr, 0xFF000000,
		W_WIDTH * W_HEIGHT * (info->screen.bits_per_pixel / 8));
}

// for every column of the screen (window width)
//   define the color of the wall (will change to textures)
//   draw the column of the wall in the screen
void	render_screen(t_info *info)
{
	int		column;
	int		color;

	clear_screen(info);
	column = -1;
	while (++column < W_WIDTH)
	{
		if (info->ray[column].wall == 'N')
			color = CO_YELLOW;
		else if (info->ray[column].wall == 'S')
			color = CO_RED;
		else if (info->ray[column].wall == 'W')
			color = CO_GREEN;
		else if (info->ray[column].wall == 'E')
			color = CO_BLUE;
		draw_wall(info, column, color);
	}
}
