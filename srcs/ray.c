/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:04:24 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/13 11:10:43 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Delta Y < 0 : Look at left
// Delta Y > 0 : Look at right
// Delta Y = 0 : The ray cannot hit a vertical wall
static float	horizontal(t_info *info, float dx, float dy)
{
	float	ratio;
	float	hit[2];
	float	side;

	side = (int)(info->player.y) + 1 - info->player.y;
	ratio = side / dy;
	if (dy < 0)
	{
		side = info->player.y - (int)(info->player.y) + 0.1f;
		ratio = -side / dy;
	}
	else if (dy == 0.0f)
		return (-1.0f);
	hit[X] = info->player.x + ratio * dx;
	hit[Y] = info->player.y + ratio * dy;
	while (1)
	{
		if (hit[X] < 0 || hit[Y] < 0 || info->map_h - 1 < hit[Y] || ft_strlen(info->map[(int)hit[Y]]) < hit[X])
			break ;
		mlx_pixel_put(info->mlx[INIT], info->mlx[WINDOW],
			hit[X] * MM_SIZE_TILE + MM_POS_X,
			hit[Y] * MM_SIZE_TILE + MM_POS_Y,
			CO_WHITE);
		if (info->map[(int)hit[Y]][(int)hit[X]] == '1')
			break ;
		if (dy > 0)
		{
			hit[Y] = hit[Y] + 1;
			hit[X] = hit[X] + (dx / dy);
		}
		else if (dy < 0)
		{
			hit[Y] = hit[Y] - 1;
			hit[X] = hit[X] - (dx / dy);
		}
	}
	return (sqrt_points(info->player.x, info->player.y, hit[X], hit[Y]));
}

// Delta X < 0 : Look at left
// Delta X > 0 : Look at right
// Delta X = 0 : The ray cannot hit a vertical wall
static float	vertical(t_info *info, float dx, float dy)
{
	float	ratio;
	float	hit[2];
	float	side;

	side = (int)(info->player.x) + 1 - info->player.x;
	ratio = side / dx;
	if (dx < 0)
	{
		side = info->player.x - (int)(info->player.x) + 0.1f;
		ratio = -side / dx;
	}
	else if (dx == 0.0f)
		return (-1.0f);
	hit[X] = info->player.x + ratio * dx;
	hit[Y] = info->player.y + ratio * dy;
	while (1)
	{
		if (hit[Y] < 0 || info->map_h - 1 < hit[Y])
			break ;
		mlx_pixel_put(info->mlx[INIT], info->mlx[WINDOW],
			hit[X] * MM_SIZE_TILE + MM_POS_X,
			hit[Y] * MM_SIZE_TILE + MM_POS_Y,
			CO_WHITE);
		if (info->map[(int)hit[Y]][(int)hit[X]] == '1')
			break ;
		if (dx > 0)
		{
			hit[X] = hit[X] + 1;
			hit[Y] = hit[Y] + (dy / dx);
		}
		else if (dx < 0)
		{
			hit[X] = hit[X] - 1;
			hit[Y] = hit[Y] - (dy / dx);
		}
	}
	return (sqrt_points(info->player.x, info->player.y, hit[X], hit[Y]));
}

// ray[X, Y]: The position of the ray
static void	ray(t_info *info, int column, float dx, float dy)
{
	float	distance[2];
	float	ray[2];

	vertical(info, dx, dy);
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
	info->rays[column].distance
		= sqrt_points(info->player.x, info->player.y, ray[X], ray[Y]);
	distance[X] = vertical(info, dx, dy);
	distance[Y] = horizontal(info, dx, dy);
	if (distance[Y] < distance[X])
	{
		if (dy > 0)
			printf("Hit SO\n");
		else
			printf("Hit NO\n");
	}
	else
	{
		if (dx > 0)
			printf("Hit ES\n");
		else
			printf("Hit WE\n");
	}
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
