/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 05:43:03 by tgrivel           #+#    #+#             */
/*   Updated: 2022/11/10 18:42:29 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// For tile top left, we need to reduce of a bit
#define CASE_NEG	0.00001f

static void
	check_hit_data(t_info *info, t_ray *ray, float hit[2], float door[2])
{
	char	data;

	data = info->map[(int)hit[Y]][(int)hit[X]];
	if (data == 'D' && !door[X])
		ft_memcpy(door, hit, 2 * sizeof(float));
	if (!door[X] && (data == 'T' || data == 'B' || data == 'X'))
		add_sprite(info, hit, data);
	if (ray->column == W_WIDTH / 2 && data == 'X'
		&& !ray->enemy_hit[X] && !door[X])
		ft_memcpy(ray->enemy_hit, hit, 2 * sizeof(float));
}

//Collision with rising horizontal line
void	horizontal_up(t_info *info, t_ray *ray, float hit[2], float door[2])
{
	float	ratio;
	float	side;

	side = info->player.pos[Y] - (int)(info->player.pos[Y]) + CASE_NEG;
	ratio = -side / ray->delta[Y];
	hit[X] = info->player.pos[X] + ratio * ray->delta[X];
	hit[Y] = info->player.pos[Y] + ratio * ray->delta[Y];
	while (info->player.pos[Y] - hit[Y] <= FOG_MAX + 2)
	{
		if (hit[X] < 0 || hit[Y] < 0 || info->mapsize[Y] - 1 < hit[Y]
			|| ft_strlen(info->map[(int)hit[Y]]) < hit[X])
			break ;
		if (info->map[(int)hit[Y]][(int)hit[X]] == '1')
			break ;
		check_hit_data(info, ray, hit, door);
		hit[Y] = hit[Y] - 1;
		hit[X] = hit[X] - (ray->delta[X] / ray->delta[Y]);
	}
	return ;
}

// Collision with the descending horizontal line
void	horizontal_down(t_info *info, t_ray *ray, float hit[2], float door[2])
{
	float	ratio;
	float	side;

	side = (int)(info->player.pos[Y]) + 1 - info->player.pos[Y];
	ratio = side / ray->delta[Y];
	hit[X] = info->player.pos[X] + ratio * ray->delta[X];
	hit[Y] = info->player.pos[Y] + ratio * ray->delta[Y];
	while (hit[Y] - info->player.pos[Y] <= FOG_MAX + 2)
	{
		if (hit[X] < 0 || hit[Y] < 0 || info->mapsize[Y] - 1 < hit[Y]
			|| ft_strlen(info->map[(int)hit[Y]]) < hit[X])
			break ;
		if (info->map[(int)hit[Y]][(int)hit[X]] == '1')
			break ;
		check_hit_data(info, ray, hit, door);
		hit[Y] = hit[Y] + 1;
		hit[X] = hit[X] + (ray->delta[X] / ray->delta[Y]);
	}
	return ;
}

// Collision with right vertical line
void	vertical_right(t_info *info, t_ray *ray, float hit[2], float door[2])
{
	float	ratio;
	float	side;

	side = (int)(info->player.pos[X]) + 1 - info->player.pos[X];
	ratio = side / ray->delta[X];
	hit[X] = info->player.pos[X] + ratio * ray->delta[X];
	hit[Y] = info->player.pos[Y] + ratio * ray->delta[Y];
	while (hit[X] - info->player.pos[X] <= FOG_MAX + 2)
	{
		if (hit[Y] < 0 || info->mapsize[Y] - 1 < hit[Y])
			break ;
		if (info->map[(int)hit[Y]][(int)hit[X]] == '1')
			break ;
		check_hit_data(info, ray, hit, door);
		hit[X] = hit[X] + 1;
		hit[Y] = hit[Y] + (ray->delta[Y] / ray->delta[X]);
	}
	return ;
}

// Collision with left vertical line
void	vertical_left(t_info *info, t_ray *ray, float hit[2], float door[2])
{
	float	ratio;
	float	side;

	side = info->player.pos[X] - (int)(info->player.pos[X]) + CASE_NEG;
	ratio = -side / ray->delta[X];
	hit[X] = info->player.pos[X] + ratio * ray->delta[X];
	hit[Y] = info->player.pos[Y] + ratio * ray->delta[Y];
	while (info->player.pos[X] - hit[X] <= FOG_MAX + 2)
	{
		if (hit[Y] < 0 || info->mapsize[Y] - 1 < hit[Y])
			break ;
		if (info->map[(int)hit[Y]][(int)hit[X]] == '1')
			break ;
		check_hit_data(info, ray, hit, door);
		hit[X] = hit[X] - 1;
		hit[Y] = hit[Y] - (ray->delta[Y] / ray->delta[X]);
	}
	return ;
}
