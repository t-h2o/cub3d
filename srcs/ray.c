/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:04:24 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/15 12:19:16 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// ray[X, Y]: The position of the ray
static void	ray(t_info *info, float delta[2], float hit[2])
{
	hit[X] = info->player.pos[X];
	hit[Y] = info->player.pos[Y];
	while (info->map[(int)(hit[Y])][(int)(hit[X])] != '1')
	{
		mlx_pixel_put(info->mlx[INIT], info->mlx[WINDOW],
			hit[X] * MM_SIZE_TILE + MM_POS_X,
			hit[Y] * MM_SIZE_TILE + MM_POS_Y,
			CO_BLUE);
		hit[X] += delta[X] / MM_SIZE_TILE;
		hit[Y] += delta[Y] / MM_SIZE_TILE;
	}
}

void	player_ray(t_info *info)
{
	int		column;

	column = 0;
	while (column < W_WIDTH)
	{
		angle_delta(info->player.angle + info->ray[column].angle,
			info->ray[column].delta);
		ray(info, info->ray[column].delta, info->ray[column].hit);
		column++;
	}
}
