/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 22:01:59 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/09/05 23:40:09 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// If the ESC key is pressed, the window closes
static int
	deal_key(int key, void *info)
{
	if (key == KEY_ESC)
		close_game(info, 0);
	else if (key == KEY_W || key == KEY_UP)
		player_move(info, PS_MOVE);
	else if (key == KEY_S || key == KEY_DOWN)
		player_move(info, -PS_MOVE);
	else if (key == KEY_D || key == KEY_RIGHT)
		player_rotate(info, PS_ROTATE);
	else if (key == KEY_A || key == KEY_LEFT)
		player_rotate(info, -PS_ROTATE);
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
	print_minimap(info);
	mlx_loop(info->mlx[INIT]);
	return (0);
}
