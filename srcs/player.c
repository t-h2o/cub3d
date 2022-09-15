/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:26:36 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/10 18:08:01 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	<math.h>

// Move player
// X = X + delta X * PS_MOVE
// Y = Y + delta Y * PS_MOVE
void
	player_move(t_info *info, float distance)
{
	float	next[2];

	next[X] = info->player.pos[X] + distance * info->player.delta[X];
	next[Y] = info->player.pos[Y] + distance * info->player.delta[Y];
	if (info->map[(int)(next[Y])][(int)(next[X])] == '1')
		return ;
	info->player.pos[X] = next[X];
	info->player.pos[Y] = next[Y];
	print_frame(info);
}

// When the player change his rotation,
// That update the delta X and Y when the player move
void
	player_rotate(t_info *info, float rotation)
{
	info->player.angle += rotation;
	if (info->player.angle < 0)
		info->player.angle += 2 * M_PI;
	if (2 * M_PI < info->player.angle)
		info->player.angle -= 2 * M_PI;
	angle_delta(info->player.angle, info->player.delta);
	print_frame(info);
}
