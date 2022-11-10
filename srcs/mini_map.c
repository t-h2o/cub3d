/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:16:47 by user42            #+#    #+#             */
/*   Updated: 2022/11/08 20:08:03 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

static int	get_mm_color(t_info *info, int y, int x)
{
	if (x >= (int)ft_strlen(info->map[y]) - 1)
		return (MM_EMPTY);
	else if (info->map[y][x] == '0')
		return (MM_GROUND);
	else if (info->map[y][x] == '1')
		return (MM_WALL);
	else if (info->map[y][x] == 'D')
		return (MM_DOOR);
	else if (info->map[y][x] == 'T')
		return (MM_TORCH);
	else if (info->map[y][x] == 'B')
		return (MM_BARREL);
	else if (info->map[y][x] == 'X')
		return (MM_ENEMY);
	else
		return (MM_EMPTY);
}

// Draw a tile of the minimap in the mm image
static void	draw_mm_tile(t_info *info, int y, int x)
{
	int		color;
	int		i;
	int		j;
	char	*dst;

	color = get_mm_color(info, y, x);
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

void	create_minimap(t_info *info)
{
	int	x;
	int	y;

	if (!info->mm_img[MAP].img)
	{
		info->mm_img[MAP].img = mlx_new_image(info->mlx[0],
				MM_SIZE_TILE * info->mapsize[X],
				MM_SIZE_TILE * info->mapsize[Y]);
		info->mm_img[MAP].addr = mlx_get_data_addr(info->mm_img[MAP].img,
				&(info->mm_img[MAP].bpp), &(info->mm_img[MAP].line_len),
				&(info->mm_img[MAP].endian));
	}
	y = -1;
	while (++y < info->mapsize[Y])
	{
		x = -1;
		while (++x < info->mapsize[X])
			draw_mm_tile(info, y, x);
	}
}

// Print the mini map
// Print the player
// Draw the rays
void	print_minimap(t_info *info)
{
	mlx_put_image_to_window(info->mlx[0], info->mlx[1],
		info->mm_img[MAP].img, MM_POS_X, MM_POS_Y);
	mlx_put_image_to_window(info->mlx[0], info->mlx[1],
		info->mm_img[PLAYER].img,
		MM_POS_X + info->player.pos[X] * MM_SIZE_TILE - MM_SIZE_PLAYER / 2,
		MM_POS_Y + info->player.pos[Y] * MM_SIZE_TILE - MM_SIZE_PLAYER / 2);
}
