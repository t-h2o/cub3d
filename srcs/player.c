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

static void	ray_cardinal(t_info *info, t_ray cardinal[4], float next[2])
{
	cardinal[NO].delta[X] = 0.0f;
	cardinal[NO].delta[Y] = -1.0f;
	cardinal[EA].delta[X] = 1.0f;
	cardinal[EA].delta[Y] = 0.0f;
	cardinal[SO].delta[X] = 0.0f;
	cardinal[SO].delta[Y] = 1.0f;
	cardinal[WE].delta[X] = -1.0f;
	cardinal[WE].delta[Y] = 0.0f;
	ft_memcpy(cardinal[NO].pos, next, 2 * sizeof(float));
	ft_memcpy(cardinal[EA].pos, next, 2 * sizeof(float));
	ft_memcpy(cardinal[SO].pos, next, 2 * sizeof(float));
	ft_memcpy(cardinal[WE].pos, next, 2 * sizeof(float));
	ray(info, &(cardinal[NO]));
	ray(info, &(cardinal[EA]));
	ray(info, &(cardinal[SO]));
	ray(info, &(cardinal[WE]));
}

static int	check_next_pos(t_info *info, float next[2])
{
	t_ray	cardinal[4];

	ray_cardinal(info, cardinal, next);
	if (cardinal[NO].distance < MIN_DISTANCE)
		return (1);
	if (cardinal[EA].distance < MIN_DISTANCE)
		return (1);
	if (cardinal[SO].distance < MIN_DISTANCE)
		return (1);
	if (cardinal[WE].distance < MIN_DISTANCE)
		return (1);
	return (0);
}

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
	if (check_next_pos(info, next))
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
	info->player.angle = angle_sum(info->player.angle, rotation);
	angle_delta(info->player.angle, info->player.delta);
	print_frame(info);
}
