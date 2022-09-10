/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:04:24 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/09 14:15:28 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// ray[X, Y]: The position of the ray
static void	ray(t_info *info, float dx, float dy)
{
	float	ray[2];

	ray[X] = info->player.x;
	ray[Y] = info->player.y;
	while (info->map[(int)(ray[Y])][(int)(ray[X])] != '1')
	{
		mlx_pixel_put(info->mlx[INIT], info->mlx[WINDOW],
			ray[X] * MM_SIZE_TILE + MM_POS_X,
			ray[Y] * MM_SIZE_TILE + MM_POS_Y,
			CO_BLUE);
		ray[X] += dx / MM_SIZE_TILE;
		ray[Y] += dy / MM_SIZE_TILE;
	}
}

void	player_ray(t_info *info)
{
	ray(info, info->player.dx, info->player.dy);
}
