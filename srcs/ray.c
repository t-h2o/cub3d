/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:04:24 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/15 10:43:20 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// ray[X, Y]: The position of the ray
static void	ray(t_info *info, float delta[2])
{
	float	ray[2];

	ray[X] = info->player.pos[X];
	ray[Y] = info->player.pos[Y];
	while (info->map[(int)(ray[Y])][(int)(ray[X])] != '1')
	{
		mlx_pixel_put(info->mlx[INIT], info->mlx[WINDOW],
			ray[X] * MM_SIZE_TILE + MM_POS_X,
			ray[Y] * MM_SIZE_TILE + MM_POS_Y,
			CO_BLUE);
		ray[X] += delta[X] / MM_SIZE_TILE;
		ray[Y] += delta[Y] / MM_SIZE_TILE;
	}
}

void	player_ray(t_info *info)
{
	ray(info, info->player.delta);
}
