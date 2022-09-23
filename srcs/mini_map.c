/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:16:47 by user42            #+#    #+#             */
/*   Updated: 2022/09/23 22:54:07 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Print a tile of the minimap
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

static void	print_mm_player(t_info *info)
{
	mlx_put_image_to_window(info->mlx[0], info->mlx[1],
		info->mm_img[PLAYER].img,
		MM_POS_X + info->player.pos[X] * MM_SIZE_TILE - MM_SIZE_PLAYER / 2,
		MM_POS_Y + info->player.pos[Y] * MM_SIZE_TILE - MM_SIZE_PLAYER / 2);
}

static void	draw_mm_rays(t_info *info)
{
	(void) info;
}

void	create_minimap(t_info *info)
{
	int	x;
	int	y;

	info->mm_image.img = mlx_new_image(info->mlx[0], 330, MM_SIZE_TILE * info->map_h);
	info->mm_image.addr = mlx_get_data_addr(info->mm_image.img,
				&(info->mm_image.bpp), &(info->mm_image.line_len),
				&(info->mm_image.endian));
	y = -1;
	while (++y < info->map_h)
	{
		x = -1;
		while (++x < 33)
			draw_mm_tile(info, info->map[y][x], y, x);
	}
}

// Print the mini map
// Print the player
// Draw the rays
void	print_minimap(t_info *info)
{
	mlx_put_image_to_window(info->mlx[0], info->mlx[1],
		info->mm_image.img, MM_POS_X, MM_POS_Y);
	print_mm_player(info);
	draw_mm_rays(info);
}
