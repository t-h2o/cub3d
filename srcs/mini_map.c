/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:16:47 by user42            #+#    #+#             */
/*   Updated: 2022/09/23 19:53:22 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Print the texture chosen with the char of the map
// Position:
//   x: Size * x_char + distance from the left
//   y: Size * y_char + distance from the top
// Get player position:
//   x: Size * x_char + ((SQUARE_MAP - SQUARE_PLAYER) / 2)
//   y: Size * y_char + ((SQUARE_MAP - SQUARE_PLAYER) / 2)
static void	draw_mm_tile(t_info *info, char c, int y, int x)
{
	int	color;
	int		i;
	int		j;
	char	*dst;

	color = 0xFF000000;
	if (c == '0')
		color = 0x00C1C1C1;
	else if (c == '1')
		color = 0x00000000;

	j = -1;
	while (++j < MM_SIZE_TILE)
	{
		i = -1;
		while (++i < MM_SIZE_TILE)
		{
			dst = info->mm_image.addr
					+ ((MM_SIZE_TILE * y + j) * info->mm_image.line_len)
					+ ((MM_SIZE_TILE * x + i) * (info->mm_image.bpp / 8));
			*(unsigned int *)dst = color;
		}
	}
}

static void	draw_mm_player(t_info *info)
{
	/*mlx_put_image_to_window(info->mlx[0], info->mlx[1],
		info->mm_img[PLAYER].img,
		MM_POS_X + info->player.pos[X] * MM_SIZE_TILE - MM_SIZE_PLAYER / 2,
		MM_POS_Y + info->player.pos[Y] * MM_SIZE_TILE - MM_SIZE_PLAYER / 2);
	*/
	int		x;
	int		y;
	char	*dst;

	y = -1;
	while (++y < MM_SIZE_PLAYER)
	{
		x = -1;
		while (++x < MM_SIZE_PLAYER)
		{
			dst = info->mm_image.addr
					+ ((int)(info->player.pos[Y] * MM_SIZE_TILE + y - MM_SIZE_PLAYER /2) * info->mm_image.line_len)
					+ ((int)(info->player.pos[X] * MM_SIZE_TILE + x) * (info->mm_image.bpp / 8));
			*(unsigned int *)dst = 0x0000FF00;
		}
	}
}

static void	draw_mm_rays(t_info *info)
{
	(void) info;
}

// Draw the mini map
// Draw the player
// Draw the rays
// Print the minimap on the window
void	print_minimap(t_info *info)
{
	int		pos_x;
	int		pos_y;

	pos_y = -1;
	while (info->map[++pos_y])
	{
		pos_x = -1;
		while (++pos_x < 33)
			draw_mm_tile(info, info->map[pos_y][pos_x], pos_y, pos_x);
	}
	draw_mm_player(info);
	draw_mm_rays(info);
	mlx_put_image_to_window(info->mlx[0], info->mlx[1],
				info->mm_image.img, MM_POS_X, MM_POS_Y);
}
