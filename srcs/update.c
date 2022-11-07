/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:19:07 by gudias            #+#    #+#             */
/*   Updated: 2022/10/28 19:50:20 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Checks keys inputs and move the player
static void	handle_key_inputs(t_info *info)
{
	if (info->inputs.forward && !info->inputs.back)
		player_move(info, PS_MOVE, 0);
	else if (info->inputs.back && !info->inputs.forward)
		player_move(info, -PS_MOVE, 0);
	if (info->inputs.m_right && !info->inputs.m_left)
		player_move(info, -PS_MOVE, 1);
	else if (info->inputs.m_left && !info->inputs.m_right)
		player_move(info, PS_MOVE, 1);
	if (info->inputs.r_right && !info->inputs.r_left)
		player_rotate(info, PS_ROTATE);
	else if (info->inputs.r_left && !info->inputs.r_right)
		player_rotate(info, -PS_ROTATE);
}

// Mouse movement
// get position of the mouse
// rotation = mouse_X_offset * RAD_PER_PIXEL
// reset position to the middle of the screen
static void	handle_mouse_move(t_info *info)
{
	int	x;
	int	y;

	my_mouse_get_pos(info->mlx[INIT], info->mlx[WINDOW], &x, &y);
	if (x == W_WIDTH / 2)
		return ;
	player_rotate(info, (x - (W_WIDTH / 2)) * (FOV / W_WIDTH) * PS_MOUSE);
	my_mouse_move(info->mlx[INIT], info->mlx[WINDOW],
		W_WIDTH / 2, W_HEIGHT / 2);
}

// Loop hook
// Updates the game
// Handle player inputs
// Refresh screen
int	update_game(t_info *info)
{
	static int	frame = 0;
	int			anim_speed_torch;

	anim_speed_torch = 10;
	if (frame > 100000000)
		frame = 0;
	if (!(frame % anim_speed_torch))
	{
		info->torch_frame++;
		if (info->torch_frame == TX_TORCH_NB)
			info->torch_frame = 0;
	}
	handle_key_inputs(info);
	handle_mouse_move(info);
	print_frame(info);
	frame++;
	return (0);
}
