/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:04:24 by tgrivel           #+#    #+#             */
/*   Updated: 2022/10/07 16:50:43 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Collect the distance to the next vertical line and the next horizontal line
static void
	ray_distance(t_info *info, t_ray *ray,
		float distance[2], float hit[2][2])
{
	distance[X] = -1.0f;
	distance[Y] = -1.0f;
	if (0.0f < ray->delta[X])
		distance[X] = vertical_right(info, hit[X], ray->delta);
	else if (ray->delta[X] < 0.0f)
		distance[X] = vertical_left(info, hit[X], ray->delta);
	if (0.0f < ray->delta[Y])
		distance[Y] = horizontal_down(info, hit[Y], ray->delta);
	else if (ray->delta[Y] < 0.0f)
		distance[Y] = horizontal_up(info, hit[Y], ray->delta);
}

// Collect the type of wall and set good values in ray
static void
	ray_type(t_info *info, t_ray *ray,
		float distance[2], float hit[2][2])
{
	if (distance[Y] < distance[X])
	{
		ray->hitdir = 1;
		ft_memcpy(ray->hit, hit[Y], 2 * sizeof(float));
		ray->distance = distance[Y];
		if (info->map[(int)ray->hit[Y]][(int)ray->hit[X]] == 'D')
			ray->wall = D;
		else if (ray->delta[Y] > 0.0f)
			ray->wall = SO;
		else
			ray->wall = NO;
	}
	else
	{
		ray->hitdir = 0;
		ft_memcpy(ray->hit, hit[X], 2 * sizeof(float));
		ray->distance = distance[X];
		if (info->map[(int)ray->hit[Y]][(int)ray->hit[X]] == 'D')
			ray->wall = D;
		else if (ray->delta[X] > 0.0f)
			ray->wall = EA;
		else
			ray->wall = WE;
	}
}

// Collect ray data
void	ray(t_info *info, t_ray *ray)
{
	float	hit[2][2];
	float	distance[2];

	ray_distance(info, ray, distance, hit);
	ray_type(info, ray, distance, hit);
}
