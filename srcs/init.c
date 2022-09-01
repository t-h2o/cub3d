/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:44:17 by gudias            #+#    #+#             */
/*   Updated: 2022/09/01 16:21:14 by gudias           ###   ########.fr       */
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

// Set default values for game textures if not defined
static void	set_default_textures(t_info *info)
{
	if (!info->texture.north)
		info->texture.north = TX_NORTH;
	if (!info->texture.south)
		info->texture.south = TX_SOUTH;
	if (!info->texture.east)
		info->texture.east = TX_EAST;
	if (!info->texture.west)
		info->texture.west = TX_WEST;
	if (!info->texture.floor)
		info->texture.north = TX_FLOOR;
	if (!info->texture.ceil)
		info->texture.ceil = TX_CEIL;
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

// Init default value of the struct
// Init mlx
// Load textures for the minimap
int	init_game(t_info *info)
{
	info->map = NULL;
	info->map_h = 0;
	info->player.x = -1.0f;
	info->texture.north = NULL;
	info->texture.south = NULL;
	info->texture.east = NULL;
	info->texture.west = NULL;
	info->texture.floor = NULL;
	info->texture.ceil = NULL;
	info->mlx[INIT] = mlx_init();
	if (!info->mlx[INIT])
		return (error_msg("Couldn't init mlx"));
	if (load_textures(info))
		return (1);
	return (0);
}
