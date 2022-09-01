/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:44:17 by gudias            #+#    #+#             */
/*   Updated: 2022/09/01 17:58:42 by gudias           ###   ########.fr       */
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
	if (!(info->texture.north))
		info->texture.north = ft_strdup(TX_NORTH);
	if (!(info->texture.south))
		info->texture.south = ft_strdup(TX_SOUTH);
	if (!(info->texture.east))
		info->texture.east = ft_strdup(TX_EAST);
	if (!(info->texture.west))
		info->texture.west = ft_strdup(TX_WEST);
//NEED to convert : "255, 116, 115" to a color
	if (!(info->texture.floor))
		info->texture.floor = ft_strdup(TX_FLOOR);
	if (!(info->texture.ceil))
		info->texture.ceil = ft_strdup(TX_CEIL);
}

static int	load_xpm_image(t_info *info, void **img, char *path)
{
	int		img_width;
	int		img_height;

	*img = mlx_xpm_file_to_image
		(info->mlx[INIT], path, &img_width, &img_height);
	if (!img || check_square(img_width, img_height))
		return (error_msg("Couldn't load texture"));
	return (0);
}

// Load textures
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

	set_default_textures(info);

	if (load_xpm_image(info, &(info->texture.img_north), info->texture.north))
		return (1);
	// same as:
	info->texture.img_south = mlx_xpm_file_to_image
		(info->mlx[INIT], info->texture.south, &img_width, &img_height);
	if ((!(info->texture.img_south)) || check_square(img_height, img_width))
		return (error_msg("Couldn't load texture"));

	info->texture.img_east = mlx_xpm_file_to_image
		(info->mlx[INIT], info->texture.east, &img_width, &img_height);
	if ((!(info->texture.img_east)) || check_square(img_height, img_width))
		return (error_msg("Couldn't load texture"));

	info->texture.img_west = mlx_xpm_file_to_image
		(info->mlx[INIT], info->texture.west, &img_width, &img_height);
	if ((!(info->texture.img_west)) || check_square(img_height, img_width))
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

// Init default value of the struct
// Init mlx
// Load the map
// Load textures
int	init_game(t_info *info, char *mapname)
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
	if (load_map(info, mapname) || load_textures(info))
		return (1);
	return (0);
}
