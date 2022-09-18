/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:50:53 by gudias            #+#    #+#             */
/*   Updated: 2022/09/22 00:34:23 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Get the value (color) of a pixel in a texture
// The position (x,y) in the texture is given by
// the scaling and the texture size
static int	get_tx_pixel(t_img_data *tx, float x_scale, float y_scale)
{
	int	pixel_value;

	pixel_value = *(unsigned int *)(tx->addr
			+ ((int)(y_scale * tx->height) * tx->line_len)
			+ ((int)(x_scale * tx->width) * (tx->bpp / 8)));
	return (pixel_value);
}

// Draw a column of the sky
static void	draw_ceil(t_info *info, int column, int offset)
{
	int		line;
	char	*dst;

	dst = info->screen.addr + (column * info->screen.bpp / 8);
	line = -1;
	while (++line < offset)
	{
		*(unsigned int *)dst = get_tx_pixel(&(info->texture[CE].img),
				(float)column / W_WIDTH,
				(float)line / (W_HEIGHT / 2));
		dst += info->screen.line_len;
	}
}

// Draw a column of a wall in the screen
// - define the texture to use for the wall
// - get address of the first pixel
// - get corresponding pixel in the texture
// - draw the pixel
// - increment by a line
static void	draw_wall(t_info *info, int column, int wall_hei, int wall_off)
{
	int			line;
	char		*dst;
	t_img_data	*tx;
	float		tx_scale;

	if (info->ray[column].wall == 'N')
		tx = &(info->texture[NO].img);
	else if (info->ray[column].wall == 'S')
		tx = &(info->texture[SO].img);
	else if (info->ray[column].wall == 'W')
		tx = &(info->texture[WE].img);
	else if (info->ray[column].wall == 'E')
		tx = &(info->texture[EA].img);
	dst = info->screen.addr + (wall_off * info->screen.line_len)
		+ (column * info->screen.bpp / 8);
	if (info->ray[column].wall == 'N' || info->ray[column].wall == 'S')
		tx_scale = info->ray[column].hit[X] - (int)info->ray[column].hit[X];
	else if (info->ray[column].wall == 'W' || info->ray[column].wall == 'E')
		tx_scale = info->ray[column].hit[Y] - (int)info->ray[column].hit[Y];
	line = -1;
	while (++line < wall_hei)
	{	
		*(unsigned int *)dst = get_tx_pixel(tx, tx_scale,
				(float)line / wall_hei);
		dst += info->screen.line_len;
	}
}

// Draw a column of the floor (single color atm)
static void	draw_floor(t_info *info, int column, int offset)
{
	int		line;
	char	*dst;

	dst = info->screen.addr + (offset * info->screen.line_len)
		+ (column * info->screen.bpp / 8);
	line = offset - 1;
	while (++line < W_HEIGHT)
	{
		*(unsigned int *)dst = get_tx_pixel(&(info->texture[FL].img),
				(float)column / W_WIDTH,
				(float)(line - (W_HEIGHT / 2)) / (W_HEIGHT / 2));
		dst += info->screen.line_len;
	}
}

// for every column of the screen (window width)
//   define correct ray distance to fix fisheye effect
//   define the height of the wall
//   define the offset of the wall (start position)
//   draw the column with sky, wall, and floor in the screen
void	render_screen(t_info *info)
{
	int		column;
	int		wall_height;
	int		wall_offset;
	float		correct_distance;

	column = -1;
	while (++column < W_WIDTH)
	{
		correct_distance = info->ray[column].distance
			* (cos(info->player.angle - info->ray[column].angle));
		wall_height = W_HEIGHT / correct_distance;
		if (wall_height > W_HEIGHT)
			wall_height = W_HEIGHT;
		wall_offset = (W_HEIGHT / 2) - (wall_height >> 1);
		draw_ceil(info, column, wall_offset);
		draw_wall(info, column, wall_height, wall_offset);
		draw_floor(info, column, wall_offset + wall_height);
	}
}
