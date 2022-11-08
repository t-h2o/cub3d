/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:50:53 by gudias            #+#    #+#             */
/*   Updated: 2022/11/08 13:37:23 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Get the value (color) of a pixel in a texture
// The position (x,y) in the texture is given by
// the scaling and the texture size
int	get_tx_pixel(t_img_data *tx, float x_scale, float y_scale)
{
	int	pixel_value;

	pixel_value = *(unsigned int *)(tx->addr
			+ ((int)(y_scale * tx->height) * tx->line_len)
			+ ((int)(x_scale * tx->width) * (tx->bpp / 8)));
	return (pixel_value);
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
	x_scale = calc_x_scaling(&(info->ray[column]));
	line = -1;
	if (wall_off < 0)
		line = -wall_off - 1;
	while (++line < wall_hei && (line + wall_off) < W_HEIGHT)
	{	
		if (info->ray[column].distance <= FOG_MAX)
		{
			*(unsigned int *)dst = get_tx_pixel(tx, x_scale,
					(float)line / wall_hei);
			add_shade(dst, info->ray[column].distance);
		}
		else
			*(unsigned int *)dst = CO_FOG;
		dst += info->screen.line_len;
	}
}

// Draw a column of the floor
//  calculate distance of the floor line
//  define X and Y position of that floor pixel
//  get corresponding pixel in texture
//  draw the pixel
static void	draw_floor(t_info *info, int column, int offset)
{
	int		line;
	char	*dst;
	float	distance;
	float	scale;
	float	floor[2];

	dst = info->screen.addr + (offset * info->screen.line_len)
		+ (column * info->screen.bpp / 8);
	line = offset - 1;
	while (++line < W_HEIGHT)
	{
		distance = W_HEIGHT / (2.0f * line - W_HEIGHT);
		scale = distance / (info->ray[column].distance);
		floor[X] = scale * info->ray[column].hit[X]
			+ (1.0f - scale) * info->player.pos[X];
		floor[Y] = scale * info->ray[column].hit[Y]
			+ (1.0f - scale) * info->player.pos[Y];
		*(unsigned int *)dst = get_tx_pixel(&(info->texture[FL].img),
				floor[X] / info->mapsize[X],
				floor[Y] / info->mapsize[Y]);
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

	column = -1;
	while (++column < W_WIDTH)
	{
		info->ray[column].distance = info->ray[column].distance
			* cos(info->ray[column].angle);
		if (info->ray[column].distance > FOG_MAX)
			wall_height = W_HEIGHT / FOG_MAX;
		else
			wall_height = W_HEIGHT / info->ray[column].distance;
		wall_offset = (W_HEIGHT - wall_height) / 2;
		draw_ceil(info, column, wall_offset);
		draw_wall(info, column, wall_height, wall_offset);
		draw_floor(info, column, wall_offset + wall_height);
	}
	if (info->spriteview)
		render_sprites(info);
}
