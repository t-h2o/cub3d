/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:04:24 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/22 00:19:00 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Collect the distance to the next vertical line and the next horizontal line
static void
	ray_distance(t_info *info, float distance[2],
		float hit[2][2], float delta[2])
{
	distance[X] = -1.0f;
	distance[Y] = -1.0f;
	if (0 < delta[X])
		distance[X] = vertical_right(info, hit[X], delta);
	else if (delta[X] < 0)
		distance[X] = vertical_left(info, hit[X], delta);
	if (0 < delta[Y])
		distance[Y] = horizontal_down(info, hit[Y], delta);
	else if (delta[Y] < 0)
		distance[Y] = horizontal_up(info, hit[Y], delta);
}

// Collect ray data
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

// Collect ray data for each column of the screen
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
