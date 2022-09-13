/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:40:59 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/21 23:41:39 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Print infos: player position (x, y, angle)
static void	print_info(t_info *info)
{
	char	message[255];

	ft_memset(message, 0, 255);
	sprintf(message, "Position X: %f", info->player.pos[X]);
	mlx_string_put(info->mlx[INIT], info->mlx[WINDOW],
		500, 10, CO_WHITE, message);
	ft_memset(message, 0, 255);
	sprintf(message, "Position Y: %f", info->player.pos[Y]);
	mlx_string_put(info->mlx[INIT], info->mlx[WINDOW],
		500, 20, CO_WHITE, message);
	ft_memset(message, 0, 255);
	sprintf(message, "P. angle  : %f", info->player.angle);
	mlx_string_put(info->mlx[INIT], info->mlx[WINDOW],
		500, 30, CO_WHITE, message);
}

// 1. Draw ray to get view informations
// 2. Render the view (walls, floor & ceilling)
// 3. Print minimap
// 4. Print informations
void	print_frame(t_info *info)
{
	mlx_clear_window(info->mlx[INIT], info->mlx[WINDOW]);
	
	player_ray(info);
	render_screen(info);

	// show rendered screen image
	mlx_put_image_to_window(info->mlx[0], info->mlx[1], info->screen.img, 0, 0);

	if (info->active_map)
		print_minimap(info);
	
	print_info(info);
}
