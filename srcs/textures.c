/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:02:07 by gudias            #+#    #+#             */
/*   Updated: 2022/10/04 18:51:57 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Load an image from xpm file
// Check if the image is a square
static int	load_xpm_image(t_info *info, t_img_data *img, char *path)
{
	img->img = mlx_xpm_file_to_image
		(info->mlx[INIT], path, &(img->width), &(img->height));
	if (!(img->img))
		return (1);
	img->addr = mlx_get_data_addr(img->img,
			&(img->bpp), &(img->line_len), &(img->endian));
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
	if (load_xpm_image(info, &(info->texture[NO].img), info->texture[NO].path)
		&& load_xpm_image(info, &(info->texture[NO].img), TX_NORTH))
		return (error_msg("Couldn't load texture"));
	if (load_xpm_image(info, &(info->texture[SO].img), info->texture[SO].path)
		&& load_xpm_image(info, &(info->texture[SO].img), TX_SOUTH))
		return (error_msg("Couldn't load texture"));
	if (load_xpm_image(info, &(info->texture[EA].img), info->texture[EA].path)
		&& load_xpm_image(info, &(info->texture[EA].img), TX_EAST))
		return (error_msg("Couldn't load texture"));
	if (load_xpm_image(info, &(info->texture[WE].img), info->texture[WE].path)
		&& load_xpm_image(info, &(info->texture[WE].img), TX_WEST))
		return (error_msg("Couldn't load texture"));
	info->texture[FL].color = convert_rgb(info->texture[FL].path);
	if (info->texture[FL].color == -1)
		info->texture[FL].color = CO_FLOOR;
	info->texture[CE].color = convert_rgb(info->texture[CE].path);
	if (info->texture[CE].color == -1)
		info->texture[CE].color = CO_CEIL;
	return (0);
}

// Load all the textures
int	load_textures(t_info *info)
{
	if (load_mm_textures(info))
		return (1);
	if (load_game_textures(info))
		return (1);
	info->screen.img = mlx_new_image(info->mlx[0], W_WIDTH, W_HEIGHT);
	info->screen.addr = mlx_get_data_addr(info->screen.img,
			&(info->screen.bpp),
			&(info->screen.line_len),
			&(info->screen.endian));
	return (0);
}
