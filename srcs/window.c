/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 22:01:59 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/10/10 17:32:40 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

static int
	deal_key(int key, t_info *info)
{
	if (key == KEY_ESC)
		close_game(info, 0);
	else if (key == KEY_W || key == KEY_UP)
		info->inputs.forward = 1;
	else if (key == KEY_S || key == KEY_DOWN)
		info->inputs.back = 1;
	else if (key == KEY_D)
		info->inputs.m_right = 1;
	else if (key == KEY_A)
		info->inputs.m_left = 1;
	else if (key == KEY_RIGHT || key == KEY_E)
		info->inputs.r_right = 1;
	else if (key == KEY_LEFT || key == KEY_Q)
		info->inputs.r_left = 1;
	else if (key == KEY_TAB)
		info->active_map = !info->active_map;
	return (0);
}

static int
	release_key(int key, t_info *info)
{
	if (key == KEY_W || key == KEY_UP)
		info->inputs.forward = 0;
	else if (key == KEY_S || key == KEY_DOWN)
		info->inputs.back = 0;
	else if (key == KEY_D)
		info->inputs.m_right = 0;
	else if (key == KEY_A)
		info->inputs.m_left = 0;
	else if (key == KEY_RIGHT || key == KEY_E)
		info->inputs.r_right = 0;
	else if (key == KEY_LEFT || key == KEY_Q)
		info->inputs.r_left = 0;
	return (0);
}

// Close the game with  an exit code of 0
static int	red_cross(t_info *info)
{
	close_game(info, 0);
	return (0);
}

// Mouse movement
// get position of the mouse
// rotation = mouse_X_offset * RAD_PER_PIXEL
// reset position to the middle of the screen
static void	mouse_move(t_info *info)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(info->mlx[WINDOW], &x, &y);
	if (x == W_WIDTH / 2)
		return ;	
	player_rotate(info, (x - (W_WIDTH / 2)) * (FOV / W_WIDTH));
	my_mouse_move(info->mlx[0], info->mlx[1], W_WIDTH / 2, W_HEIGHT / 2);
}

// Loop hook
// Update frame
static int	update_frame(t_info *info)
{
	if (info->inputs.forward)
		player_move(info, PS_MOVE, 0);
	else if (info->inputs.back)
		player_move(info, -PS_MOVE, 0);
	if (info->inputs.m_right)
		player_move(info, -PS_MOVE, 1);
	else if (info->inputs.m_left)
		player_move(info, PS_MOVE, 1);
	if (info->inputs.r_right)
		player_rotate(info, PS_ROTATE);
	else if (info->inputs.r_left)
		player_rotate(info, -PS_ROTATE);
	mouse_move(info);
	print_frame(info);
	return (0);
}

// Init and open a new window
// Define the fonction deal key for action with keys
// Start the infinite loop of the window
int	start_window(t_info *info)
{
	info->mlx[WINDOW] = mlx_new_window
		(info->mlx[INIT], W_WIDTH, W_HEIGHT, "Cub3D");
	if (!info->mlx[WINDOW])
		return (error_msg("Couldn't create window"));
	mlx_hook(info->mlx[WINDOW], 2, 1L << 0, deal_key, info);
	mlx_hook(info->mlx[WINDOW], 3, 1L << 1, release_key, info);
	mlx_hook(info->mlx[WINDOW], 17, 0L << 0, red_cross, info);
	mlx_loop_hook(info->mlx[INIT], update_frame, info);
	mlx_mouse_hide(info->mlx[INIT], info->mlx[WINDOW]);
	my_mouse_move(info->mlx[0], info->mlx[1], W_WIDTH / 2, W_HEIGHT / 2);
	print_frame(info);
	mlx_loop(info->mlx[INIT]);
	return (0);
}
