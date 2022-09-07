/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:04:24 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/08 00:21:13 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"



static void	ray(t_info *info, float dx, float dy)
{
	float	distance;
	float	ray[2];
	int		next_tile[2];

	ray[X] = info->player.x;
	ray[Y] = info->player.y;

	next_tile[X] = ray[X];
	next_tile[Y] = ray[Y];

	if (0 < dx && 0 < dy)
	{
		next_tile[X] = ray[X] + 1;
		next_tile[Y] = ray[Y] + 1;
	}
	else if (0 < dy)
		next_tile[Y] = ray[Y] + 1;
	else if (0 < dx)
		next_tile[X] = ray[X] + 1;

	distance = distance_pos(ray[X], ray[Y], (float)next_tile[X], (float)next_tile[Y]);

	printf("dis: %f\n", distance);

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
