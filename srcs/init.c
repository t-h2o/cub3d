/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:44:17 by gudias            #+#    #+#             */
/*   Updated: 2022/08/26 16:21:35 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Check if the texture is a square
static int	check_square(int height, int width)
{
	if (height != width)
		return (error_msg("Texture of the mini map is not a square"));
	return (0);
}

// Load texture for the mini map
static int	load_texture(t_info *info)
{
	int		img_width;
	int		img_height;

	info->mm[EMPTY] = mlx_xpm_file_to_image
		(info->mlx[INIT], PMM_EMPTY, &img_width, &img_height);
	if (check_square(img_height, img_width))
		return (1);
	info->mm[WALL] = mlx_xpm_file_to_image
		(info->mlx[INIT], PMM_WALL, &img_width, &img_height);
	if (check_square(img_height, img_width))
		return (1);
	return (0);
}

// Init default value of the struct
// Init mlx
// Load texture for the minimap
int	init_game(t_info *info)
{
	info->map = NULL;
	info->map_h = 0;
	info->mlx[INIT] = mlx_init();
	if (load_texture(info))
		return (1);
	return (0);
}
