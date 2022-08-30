/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:26:36 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/06 16:02:40 by tgrivel          ###   ########.fr       */
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
	if (info->map[(int)((next[Y] - MM_SIZE_PLAYER / 2) / MM_SIZE_TILE)]
		[(int)((next[X] - MM_SIZE_PLAYER / 2) / MM_SIZE_TILE)] == '1')
		return ;
	info->player.x = next[X];
	info->player.y = next[Y];
	print_minimap(info);
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
	info->player.dx = cos(info->player.angle);
	info->player.dy = sin(info->player.angle);
	print_minimap(info);
}
