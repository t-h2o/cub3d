/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:50:53 by gudias            #+#    #+#             */
/*   Updated: 2022/09/22 00:27:12 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Draw a column of the sky
// single color for now 
static void	draw_ceil(t_info *info, int column, int offset)
{
	int	line;
	char	*dst;
	int	color;
	
	color = *(unsigned int *)(info->texture[CE].img.addr + (column * info->texture[CE].img.bpp / 8));
	dst = info->screen.addr + (column * info->screen.bpp / 8);
	line = -1;
	while (++line < offset)
	{
		*(unsigned int *)dst = color;
		dst += info->screen.line_len;
	}
}

// Draw a column of a wall in the screen
// - define the texture to use for the wall
// - get address of the first pixel
// - get corresponding pixel in the texture
// - draw the pixel
// - increment by a line
static void	draw_wall(t_info *info, int column, int wall_height, int wall_offset)
{
	int	line;
	char	*dst;
	t_img_data	tx;
	float tx_scale;
	char *tx_pixel;

	if (info->ray[column].wall == 'N')
		tx = info->texture[NO].img;
	else if (info->ray[column].wall == 'S')
		tx = info->texture[SO].img;
	else if (info->ray[column].wall == 'W')
		tx = info->texture[WE].img;
	else if (info->ray[column].wall == 'E')
		tx = info->texture[EA].img;
	dst = info->screen.addr + (wall_offset * info->screen.line_len)
		+ (column * info->screen.bpp / 8);
	if (info->ray[column].wall == 'N' || info->ray[column].wall == 'S')
		tx_scale = info->ray[column].hit[X] - (int)info->ray[column].hit[X];
	else if (info->ray[column].wall == 'W' || info->ray[column].wall == 'E')
		tx_scale = info->ray[column].hit[Y] - (int)info->ray[column].hit[Y];
	line = -1;
	while (++line < wall_height)
	{
		tx_pixel = tx.addr
			+ ((int)((float)line / (float)wall_height * 512) *  tx.line_len)
			+ ((int)(tx_scale * 512) * tx.bpp / 8);
		*(unsigned int *)dst = *(unsigned int *)tx_pixel;
		dst += info->screen.line_len;
	}
}

// Draw a column of the floor (single color atm)
static void	draw_floor(t_info *info, int column, int offset)
{
	int	line;
	char	*dst;
	int	color;
	
	color = *(unsigned int *)(info->texture[FL].img.addr + (column * info->texture[FL].img.bpp / 8));
	dst = info->screen.addr + (offset * info->screen.line_len) + (column * info->screen.bpp / 8);
	line = offset - 1;
	while (++line < W_HEIGHT)
	{
		*(unsigned int *)dst = color;
		dst += info->screen.line_len;
	}
}

// for every column of the screen (window width)
//   define the height of the wall
//   define the offset of the wall (start position)
//   draw the column with sky, wall, and floor in the screen
void	render_screen(t_info *info)
{
	int		column;
	int		wall_height;
	int		wall_offset;

	column = -1;
	while (++column < W_WIDTH)
	{
		wall_height = W_HEIGHT / info->ray[column].distance;
		if (wall_height > W_HEIGHT)
			wall_height = W_HEIGHT;
		wall_offset = (W_HEIGHT / 2) - (wall_height >> 1);
		draw_ceil(info, column, wall_offset);
		draw_wall(info, column, wall_height, wall_offset);
		draw_floor(info, column, wall_offset + wall_height);
	}
}
