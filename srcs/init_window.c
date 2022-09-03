/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 11:26:54 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/09/03 11:28:35 by melogr@phy       ###   ########.fr       */
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
	info->mm_img[PLAYER] = mlx_xpm_file_to_image
		(info->mlx[INIT], MM_PLAYER, &img_width, &img_height);
	if (check_square(img_height, img_width))
		return (1);
	return (0);
}

int	init_window(t_info *info)
{
	info->mlx[INIT] = mlx_init();
	if (!info->mlx[INIT])
		return (error_msg("Couldn't init mlx"));
	if (load_textures(info))
		return (1);
	return (0);
}
