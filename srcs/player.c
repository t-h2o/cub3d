/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:26:36 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/12 16:48:10 by tgrivel          ###   ########.fr       */
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

	next[X] = info->player.x + distance * info->player.dx;
	next[Y] = info->player.y + distance * info->player.dy;
	if (info->map[(int)(next[Y])][(int)(next[X])] == '1')
		return ;
	info->player.x = next[X];
	info->player.y = next[Y];
	print_frame(info);
}

// When the player change his rotation,
// That update the delta X and Y when the player move
void
	player_rotate(t_info *info, float rotation)
{
	info->player.angle = angle_sum(info->player.angle, rotation);
	angle_delta(info->player.angle, &(info->player.dx), &(info->player.dy));
	print_frame(info);
}
