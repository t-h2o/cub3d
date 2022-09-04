/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:02:07 by gudias            #+#    #+#             */
/*   Updated: 2022/09/04 15:41:30 by gudias           ###   ########.fr       */
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

// Create an image from a single color
static int	create_color_image(t_info *info, void **img, char *path)
{
	int		color;
	int		x;
	int		y;
	t_img_data	new;
	char		*dst;

	color = convert_rgb(path);
	if (color == -1)
		return (1);
	new.img = mlx_new_image(info->mlx[INIT], 10, 10);
	new.addr = mlx_get_data_addr(new.img, &(new.bits_per_pixel),
			&(new.line_length), &(new.endian));
	y = -1;
	while (++y < 10)
	{
		x = -1;
		while (++x < 10)
		{
			dst = new.addr + (y * new.line_length + x * (new.bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
	}
	*img = new.img;
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
	if (create_color_image(info, &(info->texture.img_floor), info->texture.floor)
		&& load_xpm_image(info, &(info->texture.img_floor), TX_FLOOR))
		return (error_msg("Couldn't load texture"));
	if (create_color_image(info, &(info->texture.img_ceil), info->texture.ceil)
		&& load_xpm_image(info, &(info->texture.img_ceil), TX_CEIL))
		return (error_msg("Couldn't load texture"));
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
