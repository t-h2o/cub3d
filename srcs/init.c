/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:44:17 by gudias            #+#    #+#             */
/*   Updated: 2022/08/27 12:14:10 by gudias           ###   ########.fr       */
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

// Load textures for the mini map
static int	load_textures(t_info *info)
{
	int		img_width;
	int		img_height;

	info->mm_img[GROUND] = mlx_xpm_file_to_image
		(info->mlx[INIT], MM_GROUND, &img_width, &img_height);
	if (check_square(img_height, img_width))
		return (1);
	info->mm_img[WALL] = mlx_xpm_file_to_image
		(info->mlx[INIT], MM_WALL, &img_width, &img_height);
	if (check_square(img_height, img_width))
		return (1);
	return (0);
}

// Init default value of the struct
// Init mlx
// Load textures for the minimap
int	init_game(t_info *info)
{
	info->map = NULL;
	info->map_h = 0;
	info->mlx[INIT] = mlx_init();
	if (load_textures(info))
		return (1);
	return (0);
}
