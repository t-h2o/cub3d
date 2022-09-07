/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:04:24 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/08 01:17:39 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

static float	horizontal_dist(int line, float px, float py, float dx, float dy)
{
	float	hit_pos[2];
	float	ratio;

	ratio = (line - py) / dy;
	hit_pos[X] = px + ratio * dx;
	hit_pos[Y] = line;
	printf("hit: (%f, %f)\n", hit_pos[X], hit_pos[Y]);
	return (distance_pos(px, py, hit_pos[X], hit_pos[Y]));
}

static void	next_tile(float ray[2], int line[2], float dx, float dy)
{
	line[X] = ray[X];
	line[Y] = ray[Y];
	if (0 < dx && 0 < dy)
	{
		line[X] = ray[X] + 1;
		line[Y] = ray[Y] + 1;
	}
	else if (0 < dy)
		line[Y] = ray[Y] + 1;
	else if (0 < dx)
		line[X] = ray[X] + 1;
}

static void	ray(t_info *info, float dx, float dy)
{
	float	distance;
	float	ray[2];
	int		line[2];

	ray[X] = info->player.x;
	ray[Y] = info->player.y;

	next_tile(ray, line, dx, dy);
	distance = horizontal_dist(line[Y], ray[X], ray[Y], dx, dy);

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
