/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:04:24 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/12 16:51:40 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// ray[X, Y]: The position of the ray
static void	ray(t_info *info, int column, float dx, float dy)
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
	info->rays[column].hit[X] = ray[X];
	info->rays[column].hit[Y] = ray[Y];
}

void	player_ray(t_info *info)
{
	int		column;

	column = 0;
	info->rays[column].angle = angle_sum(info->player.angle, -FOV / 2);
	while (column < W_WIDTH)
	{
		angle_delta(info->rays[column].angle,
			&(info->rays[column].delta[X]),
			&(info->rays[column].delta[Y]));
		ray(info, column, info->rays[column].delta[X],
			info->rays[column].delta[Y]);
		column++;
		info->rays[column].angle
			= angle_sum(info->rays[column - 1].angle, FOV / W_WIDTH);
	}
}
