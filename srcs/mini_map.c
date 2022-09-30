/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:16:47 by user42            #+#    #+#             */
/*   Updated: 2022/09/30 17:53:16 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Draw a tile of the minimap in the mm image
static void	draw_mm_tile(t_info *info, char c, int y, int x)
{
	int	color;
	int		i;
	int		j;
	char	*dst;

	color = 0x70303030;
	if (c == '0')
		color = MM_GROUND;
	else if (c == '1')
		color = MM_WALL;
	j = -1;
	while (++j < MM_SIZE_TILE)
	{
		i = -1;
		while (++i < MM_SIZE_TILE)
		{
			dst = info->mm_img[MAP].addr
					+ ((MM_SIZE_TILE * y + j) * info->mm_img[MAP].line_len)
					+ ((MM_SIZE_TILE * x + i) * (info->mm_img[MAP].bpp / 8));
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

	info->mm_img[MAP].img = mlx_new_image(info->mlx[0], 330, MM_SIZE_TILE * info->map_h);
	info->mm_img[MAP].addr = mlx_get_data_addr(info->mm_img[MAP].img,
				&(info->mm_img[MAP].bpp), &(info->mm_img[MAP].line_len),
				&(info->mm_img[MAP].endian));
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
		info->mm_img[MAP].img, MM_POS_X, MM_POS_Y);
	print_mm_player(info);
	draw_mm_rays(info);
}
