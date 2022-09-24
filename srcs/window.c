/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 22:01:59 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/09/10 18:39:30 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// If the ESC key is pressed, the window closes
static int
	deal_key(int key, t_info *info)
{
	if (key == KEY_ESC)
		close_game(info, 0);
	else if (key == KEY_W || key == KEY_UP)
		player_move(info, PS_MOVE, 0);
	else if (key == KEY_S || key == KEY_DOWN)
		player_move(info, -PS_MOVE, 0);
	else if (key == KEY_D)
		player_move(info, -PS_MOVE, 1);
	else if (key == KEY_A)
		player_move(info, PS_MOVE, 1);
	else if (key == KEY_RIGHT)
		player_rotate(info, PS_ROTATE);
	else if (key == KEY_LEFT)
		player_rotate(info, -PS_ROTATE);
	else if (key == KEY_TAB)
	{
		info->active_map = !info->active_map;
		print_frame(info);
	}
	return (0);
}

// Close the game with  an exit code of 0
static int	red_cross(t_info *info)
{
	close_game(info, 0);
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
	mlx_hook(info->mlx[WINDOW], 2, 1, deal_key, info);
	mlx_hook(info->mlx[WINDOW], 17, 0L << 0, red_cross, info);
	print_frame(info);
	mlx_loop(info->mlx[INIT]);
	return (0);
}
