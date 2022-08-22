/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 22:01:59 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/08/20 09:59:53 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Destroy the window and exit the program
static void
	destroy_window(t_info *info)
{
	mlx_destroy_window(info->mlx[INIT], info->mlx[WINDOW]);
	exit(0);
}

// If the ESC key is pressed, the window closes
static int
	deal_key(int key, void *info)
{
	if (key == KEY_ESC)
		destroy_window(info);
	return (0);
}

// Init and open a new window
// Define the fonction deal key for action with keys
// Start the infinite loop of the window
int	start_window(t_info *info)
{
	info->mlx[INIT] = mlx_init();
	info->mlx[WINDOW]
		= mlx_new_window(info->mlx[INIT], W_WIDTH, W_HEIGHT, "Cub3D");
	mlx_key_hook(info->mlx[WINDOW], deal_key, (void *)info);
	mlx_loop(info->mlx[INIT]);
	return (0);
}
