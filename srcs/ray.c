/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:04:24 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/13 15:05:28 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Return the distance to the next horizontal wall or -1 if there is no distance
static float	horizontal(t_info *info, float hit[2], float dx, float dy)
{
	float	ratio;
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
		if (hit[X] < 0 || hit[Y] < 0 || info->map_h - 1 < hit[Y]
			|| ft_strlen(info->map[(int)hit[Y]]) < hit[X]
			|| info->map[(int)hit[Y]][(int)hit[X]] == '1')
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

// Return the distance to the next vertical wall or -1 if there is no distance
static float	vertical(t_info *info, float hit[2], float dx, float dy)
{
	float	ratio;
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
		if (hit[Y] < 0 || info->map_h - 1 < hit[Y]
			|| info->map[(int)hit[Y]][(int)hit[X]] == '1')
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

// Fill for rays
//   * distance
//   * wall orientation
static void	ray(t_info *info, int column, float dx, float dy)
{
	float	hit[2][2];
	float	distance[2];

	distance[X] = vertical(info, hit[X], dx, dy);
	distance[Y] = horizontal(info, hit[Y], dx, dy);
	if (distance[Y] != -1.0f && distance[Y] < distance[X])
	{
		ft_memcpy(info->rays[column].hit, hit[Y], 2 * sizeof(float));
		info->rays[column].distance = distance[Y];
		if (dy > 0)
			info->rays[column].wall = 'S';
		else
			info->rays[column].wall = 'N';
	}
	else
	{
		ft_memcpy(info->rays[column].hit, hit[X], 2 * sizeof(float));
		info->rays[column].distance = distance[X];
		if (dx > 0)
			info->rays[column].wall = 'E';
		else
			info->rays[column].wall = 'W';
	}
}

// Fill for rays
//   * angle
//   * delta X
//   * delta Y
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
