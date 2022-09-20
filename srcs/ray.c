/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:04:24 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/20 05:53:39 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

static void
	ray_distance(t_info *info, float distance[2],
		float hit[2][2], float delta[2])
{
	distance[X] = -1.0f;
	distance[Y] = -1.0f;
	if (0.0f < delta[X])
		distance[X] = vertical_right(info, hit[X], delta[X], delta[Y]);
	if (delta[X] < 0.0f)
		distance[X] = vertical_left(info, hit[X], delta[X], delta[Y]);
	if (0.0f < delta[Y])
		distance[Y] = horizontal_down(info, hit[Y], delta[X], delta[Y]);
	if (delta[Y] < 0.0f)
		distance[Y] = horizontal_up(info, hit[Y], delta[X], delta[Y]);
}

// ray[X, Y]: The position of the ray
static void	ray(t_info *info, int column, float delta[2])
{
	float	hit[2][2];
	float	distance[2];

	ray_distance(info, distance, hit, delta);
	if (distance[Y] < distance[X])
	{
		ft_memcpy(info->ray[column].hit, hit[Y], 2 * sizeof(float));
		info->ray[column].distance = distance[Y];
		if (delta[Y] > 0)
			info->ray[column].wall = 'S';
		else
			info->ray[column].wall = 'N';
	}
	else
	{
		ft_memcpy(info->ray[column].hit, hit[X], 2 * sizeof(float));
		info->ray[column].distance = distance[X];
		if (delta[X] > 0)
			info->ray[column].wall = 'E';
		else
			info->ray[column].wall = 'W';
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
		ray(info, column, info->ray[column].delta);
		column++;
	}
}
