/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:26:36 by tgrivel           #+#    #+#             */
/*   Updated: 2022/11/09 20:13:47 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	<math.h>

// Move player
void
	player_move(t_info *info, float distance, int side)
{
	float	next[2];

	if (side)
	{
		next[X] = info->player.pos[X] + distance * info->player.delta[Y];
		next[Y] = info->player.pos[Y] + distance * -info->player.delta[X];
	}
	else
	{
		next[X] = info->player.pos[X] + distance * info->player.delta[X];
		next[Y] = info->player.pos[Y] + distance * info->player.delta[Y];
	}
	if (info->map[(int)(next[Y])][(int)(next[X])] == '1'
			|| info->map[(int)(next[Y])][(int)(next[X])] == 'T'
			|| info->map[(int)(next[Y])][(int)(next[X])] == 'B'
			|| info->map[(int)(next[Y])][(int)(next[X])] == 'X'
			|| (info->map[(int)(next[Y])][(int)(next[X])] == 'D'
			&& find_door(info, next)->frame < TX_DOOR_NB - 1))
		return ;
	info->player.pos[X] = next[X];
	info->player.pos[Y] = next[Y];
}

// When the player change his rotation,
// That update the delta X and Y when the player move
void
	player_rotate(t_info *info, float rotation)
{
	info->player.angle = angle_sum(info->player.angle, rotation);
	angle_delta(info->player.angle, info->player.delta);
}

// Player Action
// When player press 'E'
void
	player_action(t_info *info)
{
	t_ray	*mid_ray;
	t_door	*door;

	mid_ray = &(info->ray[W_WIDTH / 2]);
	if (mid_ray->door_hit[X] && mid_ray->door_dist < 1.5f)
	{
		door = find_door(info, mid_ray->door_hit);
		if (door->frame == 0)
			door->opening = 1;
		else if (door->frame == TX_DOOR_NB - 1)
			door->closing = 1;
	}
}

void
	player_attack(t_info *info)
{
	t_ray	*mid_ray;

	mid_ray = &(info->ray[W_WIDTH / 2]);
	if (mid_ray->enemy_hit[X])
	{
		info->map[(int)mid_ray->enemy_hit[Y]][(int)mid_ray->enemy_hit[X]] = '0';
		create_minimap(info);
	}
}
