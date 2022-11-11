/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:04:24 by tgrivel           #+#    #+#             */
/*   Updated: 2022/11/10 17:30:52 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Collect the distance to the next vertical line and the next horizontal line
static void
	ray_cast(t_info *info, t_ray *ray, float hit[2][2], float door[2][2])
{
	door[X][X] = 0.0f;
	door[Y][X] = 0.0f;
	if (0.0f < ray->delta[X])
		vertical_right(info, ray, hit[X], door[X]);
	else if (ray->delta[X] < 0.0f)
		vertical_left(info, ray, hit[X], door[X]);
	if (0.0f < ray->delta[Y])
		horizontal_down(info, ray, hit[Y], door[Y]);
	else if (ray->delta[Y] < 0.0f)
		horizontal_up(info, ray, hit[Y], door[Y]);
}

// Collect the type of wall and set good values in ray
static void
	ray_type(t_info *info, t_ray *ray, float hit[2][2])
{
	float	distance[2];

	distance[X] = sqrt_points(info->player.pos, hit[X]);
	distance[Y] = sqrt_points(info->player.pos, hit[Y]);
	if (distance[Y] < distance[X])
	{
		ray->hitdir = 1;
		ft_memcpy(ray->hit, hit[Y], 2 * sizeof(float));
		ray->distance = distance[Y];
		if (ray->delta[Y] > 0.0f)
			ray->wall = SO;
		else
			ray->wall = NO;
	}
	else
	{
		ray->hitdir = 0;
		ft_memcpy(ray->hit, hit[X], 2 * sizeof(float));
		ray->distance = distance[X];
		if (ray->delta[X] > 0.0f)
			ray->wall = EA;
		else
			ray->wall = WE;
	}
}

static void
	ray_doors(t_info *info, t_ray *ray, float door[2][2])
{
	float	distance[2];

	distance[X] = sqrt_points(info->player.pos, door[X]);
	distance[Y] = sqrt_points(info->player.pos, door[Y]);
	if (distance[Y] < distance[X] && distance[Y] < ray->distance)
	{
		ray->doordir = 1;
		ft_memcpy(ray->door_hit, door[Y], 2 * sizeof(float));
		ray->door_dist = distance[Y] * cos(ray->angle);
	}
	else if (distance[X] < distance[Y] && distance[X] < ray->distance)
	{	
		ray->doordir = 0;
		ft_memcpy(ray->door_hit, door[X], 2 * sizeof(float));
		ray->door_dist = distance[X] * cos(ray->angle);
	}
}

// Collect ray data
void	ray(t_info *info, t_ray *ray)
{
	float	hit[2][2];
	float	door[2][2];

	ray_cast(info, ray, hit, door);
	ray_type(info, ray, hit);
	ray_doors(info, ray, door);
}
