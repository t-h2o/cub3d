/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:50:53 by gudias            #+#    #+#             */
/*   Updated: 2022/09/22 00:19:46 by gudias           ###   ########.fr       */
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
static void	draw_wall(t_info *info, int column, void *tx_img)
{
	int		wall_height;
	int		wall_offset;
	char	*dst;
	t_img_data	new;

	wall_height = W_HEIGHT / info->ray[column].distance;
	if (wall_height > W_HEIGHT)
		wall_height = W_HEIGHT;
	wall_offset = (W_HEIGHT / 2) - (wall_height >> 1);
	dst = info->screen.addr + (wall_offset * info->screen.line_length)
		+ (column * info->screen.bits_per_pixel / 8);

	new.addr = mlx_get_data_addr(tx_img, &(new.bits_per_pixel), &(new.line_length), &(new.endian));
	char *tx_dst;
	int	line = -1;
	while (++line < wall_height)
	{
		tx_dst = new.addr + ((int)((float)line / (float)wall_height * 512) *  new.line_length) + (10 * new.bits_per_pixel / 8);
		*(unsigned int *)dst = *(unsigned int *)tx_dst;
		dst += info->screen.line_length;
	}
}

static void	clear_screen(t_info *info)
{
	ft_memset(info->screen.addr, 0xFF,
		W_WIDTH * W_HEIGHT * (info->screen.bits_per_pixel / 8));
}

// for every column of the screen (window width)
//   define the color of the wall (will change to textures)
//   draw the column of the wall in the screen
void	render_screen(t_info *info)
{
	int		column;
	void	*tx_img;

	clear_screen(info);
	column = -1;
	while (++column < W_WIDTH)
	{
		if (info->ray[column].wall == 'N')
			tx_img = info->texture[NO].img;
		else if (info->ray[column].wall == 'S')
			tx_img = info->texture[SO].img;
		else if (info->ray[column].wall == 'W')
			tx_img = info->texture[WE].img;
		else if (info->ray[column].wall == 'E')
			tx_img = info->texture[EA].img;
		draw_wall(info, column, tx_img);
	}
}
