/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:40:59 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/10 19:05:59 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Position player
static void	print_info(t_info *info)
{
	char	message[255];

	ft_memset(message, 0, 255);
	sprintf(message, "Position X: %f", info->player.x);
	mlx_string_put(info->mlx[INIT], info->mlx[WINDOW],
		500, 10, CO_WHITE, message);
	ft_memset(message, 0, 255);
	sprintf(message, "Position Y: %f", info->player.y);
	mlx_string_put(info->mlx[INIT], info->mlx[WINDOW],
		500, 20, CO_WHITE, message);
	ft_memset(message, 0, 255);
	sprintf(message, "P. angle  : %f", info->player.angle);
	mlx_string_put(info->mlx[INIT], info->mlx[WINDOW],
		500, 30, CO_WHITE, message);
}

// 1. Print floor and ceilling
// 2. Print walls
// 3. Print minimap
// 4. Print informations
void	print_frame(t_info *info)
{
	mlx_clear_window(info->mlx[INIT], info->mlx[WINDOW]);
	if (info->active_map)
		print_minimap(info);
	player_ray(info);
	print_info(info);
}
