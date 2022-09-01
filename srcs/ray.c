/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:04:24 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/05 17:07:24 by tgrivel          ###   ########.fr       */
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

	pixel_x = info->player.x;
	pixel_y = info->player.y;
	while (info->map[(int)(pixel_y)][(int)(pixel_x)] != '1')
	{
		mlx_pixel_put(info->mlx[INIT], info->mlx[WINDOW],
			pixel_x * MM_SIZE_TILE + MM_POS_X,
			pixel_y * MM_SIZE_TILE + MM_POS_X, CO_BLUE);
		pixel_x += 1.0f * info->player.dx;
		pixel_y += 1.0f * info->player.dy;
	}
	return (0);
}
