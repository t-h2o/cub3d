/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:16:47 by user42            #+#    #+#             */
/*   Updated: 2022/08/27 17:28:00 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Print the texture chosen with the char of the map
// Position:
//   x: Size * x_char + distance from the left
//   y: Size * y_char + distance from the top
static void	print_square(t_info *info, char c, int y, int x)
{
	if (c == '0' || c == 'N' || c == 'E' || c == 'S' || c == 'W')
		mlx_put_image_to_window(info->mlx[0], info->mlx[1],
				info->mm_img[GROUND],
				x * MM_TILESIZE + MM_POS_X,
				y * MM_TILESIZE + MM_POS_Y);
	if (c == '1')
		mlx_put_image_to_window(info->mlx[0], info->mlx[1],
			info->mm_img[WALL],
			x * MM_TILESIZE + MM_POS_X,
			y * MM_TILESIZE + MM_POS_Y);
}

// Print the mini map
void	print_minimap(t_info *info)
{
	int		pos_x;
	int		pos_y;

	pos_y = -1;
	while (info->map[++pos_y])
	{
		pos_x = -1;
		while (info->map[pos_y][++pos_x])
			print_square(info, info->map[pos_y][pos_x], pos_y, pos_x);
	}
}
