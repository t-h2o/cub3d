/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 12:26:36 by tgrivel           #+#    #+#             */
/*   Updated: 2022/08/29 13:27:13 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	<math.h>

// Move player
// X = X + delta X * SENSE_MOVE
// Y = Y + delta Y * SENSE_MOVE
void
	player_move(t_info *info, float distance)
{
	info->pos_player[X] += distance * info->pos_player[PDX];
	info->pos_player[Y] += distance * info->pos_player[PDY];
	print_minimap(info);
}

// When the player change his rotation,
// That update the delta X and Y when the player move
void
	player_angle(t_info *info, float rotation)
{
	info->pos_player[A] += rotation;
	if (info->pos_player[A] < 0)
		info->pos_player[A] += 2 * PI;
	if (2 * PI < info->pos_player[A])
		info->pos_player[A] -= 2 * PI;
	info->pos_player[PDX] = cos(info->pos_player[A]) * 5;
	info->pos_player[PDY] = sin(info->pos_player[A]) * 5;
	print_minimap(info);
}
