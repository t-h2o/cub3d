/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:16:47 by user42            #+#    #+#             */
/*   Updated: 2022/08/26 17:44:47 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Print the texture chosen with the char of the map
// Position:
//   x: Size * x_char + distance from the left
//   y: Size * y_char + distance from the top
static void	print_sqare(t_info *info, char c, int y, int x)
{
	if (c == '0' || c == 'N' || c == 'E' || c == 'S' || c == 'W')
		mlx_put_image_to_window(info->mlx[0], info->mlx[1],
			info->mm[EMPTY], x * MM_SQUARE + MM_LEFT, y * MM_SQUARE + MM_TOP);
	if (c == '1')
		mlx_put_image_to_window(info->mlx[0], info->mlx[1],
			info->mm[WALL], x * MM_SQUARE + MM_LEFT, y * MM_SQUARE + MM_TOP);
}

// Print the mini map
static void	print_map(t_info *info)
{
	int		pos_x;
	int		pos_y;

	pos_y = -1;
	while (info->map[++pos_y])
	{
		pos_x = -1;
		while (info->map[pos_y][++pos_x])
			print_sqare(info, info->map[pos_y][pos_x], pos_y, pos_x);
	}
}

void	mini_map(t_info *info)
{
	print_map(info);
}
