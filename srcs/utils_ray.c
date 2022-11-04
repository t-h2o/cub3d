/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 05:43:03 by tgrivel           #+#    #+#             */
/*   Updated: 2022/10/07 00:40:45 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// For tile top left, we need to reduce of a bit
#define CASE_NEG	0.00001f

//Collision with rising horizontal line
float	horizontal_up(t_info *info, float hit[2], float delta[2])
{
	float	ratio;
	float	side;

	side = info->player.pos[Y] - (int)(info->player.pos[Y]) + CASE_NEG;
	ratio = -side / delta[Y];
	hit[X] = info->player.pos[X] + ratio * delta[X];
	hit[Y] = info->player.pos[Y] + ratio * delta[Y];
	while (1)
	{
		if (hit[X] < 0 || hit[Y] < 0 || info->mapsize[Y] - 1 < hit[Y]
			|| ft_strlen(info->map[(int)hit[Y]]) < hit[X])
			break ;
		if (info->map[(int)hit[Y]][(int)hit[X]] == '1'
				|| info->map[(int)hit[Y]][(int)hit[X]] == 'D')
			break ;
		hit[Y] = hit[Y] - 1;
		hit[X] = hit[X] - (delta[X] / delta[Y]);
	}
	return (sqrt_points(info->player.pos, hit));
}

// Collision with the descending horizontal line
float	horizontal_down(t_info *info, float hit[2], float delta[2])
{
	float	ratio;
	float	side;

	side = (int)(info->player.pos[Y]) + 1 - info->player.pos[Y];
	ratio = side / delta[Y];
	hit[X] = info->player.pos[X] + ratio * delta[X];
	hit[Y] = info->player.pos[Y] + ratio * delta[Y];
	while (1)
	{
		if (hit[X] < 0 || hit[Y] < 0 || info->mapsize[Y] - 1 < hit[Y]
			|| ft_strlen(info->map[(int)hit[Y]]) < hit[X])
			break ;
		if (info->map[(int)hit[Y]][(int)hit[X]] == '1'
				|| info->map[(int)hit[Y]][(int)hit[X]] == 'D')
			break ;
		hit[Y] = hit[Y] + 1;
		hit[X] = hit[X] + (delta[X] / delta[Y]);
	}
	return (sqrt_points(info->player.pos, hit));
}

// Collision with right vertical line
float	vertical_right(t_info *info, float hit[2], float delta[2])
{
	float	ratio;
	float	side;

	side = (int)(info->player.pos[X]) + 1 - info->player.pos[X];
	ratio = side / delta[X];
	hit[X] = info->player.pos[X] + ratio * delta[X];
	hit[Y] = info->player.pos[Y] + ratio * delta[Y];
	while (1)
	{
		if (hit[Y] < 0 || info->mapsize[Y] - 1 < hit[Y])
			break ;
		if (info->map[(int)hit[Y]][(int)hit[X]] == '1'
				|| info->map[(int)hit[Y]][(int)hit[X]] == 'D')
			break ;
		hit[X] = hit[X] + 1;
		hit[Y] = hit[Y] + (delta[Y] / delta[X]);
	}
	return (sqrt_points(info->player.pos, hit));
}

// Collision with left vertical line
float	vertical_left(t_info *info, float hit[2], float delta[2])
{
	float	ratio;
	float	side;

	side = info->player.pos[X] - (int)(info->player.pos[X]) + CASE_NEG;
	ratio = -side / delta[X];
	hit[X] = info->player.pos[X] + ratio * delta[X];
	hit[Y] = info->player.pos[Y] + ratio * delta[Y];
	while (1)
	{
		if (hit[Y] < 0 || info->mapsize[Y] - 1 < hit[Y])
			break ;
		if (info->map[(int)hit[Y]][(int)hit[X]] == '1'
				|| info->map[(int)hit[Y]][(int)hit[X]] == 'D')
			break ;
		hit[X] = hit[X] - 1;
		hit[Y] = hit[Y] - (delta[Y] / delta[X]);
	}
	return (sqrt_points(info->player.pos, hit));
}
