/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:04:24 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/05 17:04:57 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// pixel_x & pixel_y are the pixel location
// 1. the pixel location take the player location
// 2. while the pixel location isn't in a wall
//    it can be print
//    pixel location is increase with delta X and delta Y
int	ray(t_info *info)
{
	float	pixel_x;
	float	pixel_y;

	pixel_x = info->player.x + MM_POS_X - MM_SIZE_PLAYER / 2;
	pixel_y = info->player.y + MM_POS_Y - MM_SIZE_PLAYER / 2;
	while (info->map[(int)((pixel_y - MM_SIZE_TILE) / MM_SIZE_TILE)]
		[(int)((pixel_x - MM_SIZE_TILE) / MM_SIZE_TILE)] != '1')
	{
		mlx_pixel_put(info->mlx[INIT], info->mlx[WINDOW],
			pixel_x, pixel_y, CO_BLUE);
		pixel_x += 0.2f * info->player.dx;
		pixel_y += 0.2f * info->player.dy;
	}
	return (0);
}
