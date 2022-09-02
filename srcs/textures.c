/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:02:07 by gudias            #+#    #+#             */
/*   Updated: 2022/09/02 16:15:15 by gudias           ###   ########.fr       */
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

// Load an image from xpm file
// Check if the image is a square
static int	load_xpm_image(t_info *info, void **img, char *path)
{
	int		img_width;
	int		img_height;

	*img = mlx_xpm_file_to_image
		(info->mlx[INIT], path, &img_width, &img_height);
	if (!(*img))
		return (1);
	if (check_square(img_width, img_height))
	{
		mlx_destroy_image(info->mlx[INIT], *img);
		return (1);
	}
	return (0);
}

// Load textures for the minimap
static int	load_mm_textures(t_info *info)
{
	if (load_xpm_image(info, &(info->mm_img[GROUND]), MM_GROUND))
		return (1);
	if (load_xpm_image(info, &(info->mm_img[WALL]), MM_WALL))
		return (1);
	if (load_xpm_image(info, &(info->mm_img[PLAYER]), MM_PLAYER))
		return (1);
	return (0);
}

// Load textures for the game
// 	try to load from path defined in mapfile
// 	or fallback to default texture if failed
static int	load_game_textures(t_info *info)
{
	if (load_xpm_image(info, &(info->texture.img_north), info->texture.north)
		&& load_xpm_image(info, &(info->texture.img_north), TX_NORTH))
		return (error_msg("Couldn't load texture"));
	if (load_xpm_image(info, &(info->texture.img_south), info->texture.south)
		&& load_xpm_image(info, &(info->texture.img_south), TX_SOUTH))
		return (error_msg("Couldn't load texture"));
	if (load_xpm_image(info, &(info->texture.img_east), info->texture.east)
		&& load_xpm_image(info, &(info->texture.img_east), TX_EAST))
		return (error_msg("Couldn't load texture"));
	if (load_xpm_image(info, &(info->texture.img_west), info->texture.west)
		&& load_xpm_image(info, &(info->texture.img_west), TX_WEST))
		return (error_msg("Couldn't load texture"));

/* NEED to draw an image based on the color instead of loading a texture
 * for the FLOOR and the CEILLING

	info->texture.img_floor = mlx_xpm_file_to_image
		(info->mlx[INIT], info->texture.floor, &img_width, &img_height);
	if ((!(info->texture.img_floor)) || check_square(img_height, img_width))
		return (error_msg("Couldn't load texture"));

	info->texture.img_ceil = mlx_xpm_file_to_image
		(info->mlx[INIT], info->texture.ceil, &img_width, &img_height);
	if ((!(info->texture.img_ceil)) || check_square(img_height, img_width))
		return (error_msg("Couldn't load texture"));
*/
	return (0);
}

// Load all the textures
int	load_textures(t_info *info)
{
	if (load_mm_textures(info))
		return (1);
	if (load_game_textures(info))
		return (1);
	return (0);
}
