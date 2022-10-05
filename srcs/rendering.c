/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:50:53 by gudias            #+#    #+#             */
/*   Updated: 2022/10/05 19:15:43 by gudias           ###   ########.fr       */
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

static void	add_shade(char *dst, float distance)
{
	float		shading;

	if (distance <= 3.0f) //FOG MIN
		return ;
	shading = 1 / (distance - 2);
	dst[0] = (unsigned char)dst[0] * shading;
	dst[1] = (unsigned char)dst[1] * shading;
	dst[2] = (unsigned char)dst[2] * shading;
}

// Draw a column of the sky
//  adds offset to the sky depending on player orientation
//  sky_offset is between 0.0 and 1.0
//  sky_offset = (player.angle + (column / W_WIDTH) * FOV) / (2 * PI)
static void	draw_ceil(t_info *info, int column, int offset)
{
	int		line;
	char	*dst;
	float	sky_offset;

	dst = info->screen.addr + (column * info->screen.bpp / 8);
	sky_offset = angle_sum(info->player.angle - FOV / 2 + M_PI / 2,
			((float)column / (float)W_WIDTH) * FOV) / (2 * M_PI);
	line = -1;
	while (++line < offset)
	{
		*(unsigned int *)dst = get_tx_pixel(&(info->texture[CE].img),
				sky_offset,
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
	float		x_scale;

	tx = &(info->texture[info->ray[column].wall].img);
	dst = info->screen.addr + (column * info->screen.bpp / 8);
	if (wall_off > 0)
		dst += (wall_off * info->screen.line_len);
	if (info->ray[column].wall == NO || info->ray[column].wall == SO)
		x_scale = info->ray[column].hit[X] - (int)info->ray[column].hit[X];
	else
		x_scale = info->ray[column].hit[Y] - (int)info->ray[column].hit[Y];
	line = -1;
	if (wall_off < 0)
		line = -wall_off - 1;
	while (++line < wall_hei && (line + wall_off) < W_HEIGHT)
	{	
		if (info->ray[column].distance <= 7.5f) //MAX VIEW (FOG MAX)
		{
			*(unsigned int *)dst = get_tx_pixel(tx, x_scale,
					(float)line / wall_hei);
			add_shade(dst, info->ray[column].distance);
		}
		else
			*(unsigned int *)dst = 0x08080808; //CO_FOG

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
	float	correct_distance;

	column = -1;
	while (++column < W_WIDTH)
	{
		correct_distance = info->ray[column].distance
			* cos(info->ray[column].angle);
		if (correct_distance > 7.5f)
			wall_height = W_HEIGHT / 7.5f;
		else
			wall_height = W_HEIGHT / correct_distance;
		wall_offset = (W_HEIGHT - wall_height) / 2;
		draw_ceil(info, column, wall_offset);
		draw_wall(info, column, wall_height, wall_offset);
		draw_floor(info, column, wall_offset + wall_height);
	}
}
