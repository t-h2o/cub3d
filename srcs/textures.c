/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:02:07 by gudias            #+#    #+#             */
/*   Updated: 2022/10/18 13:53:26 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Create an image from a single color
static int	create_image(t_info *info, t_img_data *img, char *path)
{
	int			color;
	int			x;
	int			y;
	char		*dst;

	color = convert_rgb(path);
	if (color == -1)
		return (1);
	img->img = mlx_new_image(info->mlx[INIT], W_WIDTH, W_HEIGHT / 2);
	img->addr = mlx_get_data_addr(img->img,
			&(img->bpp), &(img->line_len), &(img->endian));
	y = -1;
	while (++y < W_HEIGHT / 2)
	{
		x = -1;
		while (++x < W_WIDTH)
		{
			dst = img->addr + (y * img->line_len
					+ x * (img->bpp / 8));
			*(unsigned int *)dst = color;
		}
	}
	return (0);
}

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

// Load textures for the game
//	mm player, walls, pov
// 	try to load from path defined in mapfile
// 	or fallback to default texture if failed
static int	load_game_textures(t_info *info)
{
	if (load_xpm_image(info, &(info->texture[NO].img), info->texture[NO].path)
		&& load_xpm_image(info, &(info->texture[NO].img), TX_NORTH))
		return (1);
	if (load_xpm_image(info, &(info->texture[SO].img), info->texture[SO].path)
		&& load_xpm_image(info, &(info->texture[SO].img), TX_SOUTH))
		return (1);
	if (load_xpm_image(info, &(info->texture[EA].img), info->texture[EA].path)
		&& load_xpm_image(info, &(info->texture[EA].img), TX_EAST))
		return (1);
	if (load_xpm_image(info, &(info->texture[WE].img), info->texture[WE].path)
		&& load_xpm_image(info, &(info->texture[WE].img), TX_WEST))
		return (1);
	if (create_image(info, &(info->texture[FL].img), info->texture[FL].path)
		&& load_xpm_image(info, &(info->texture[FL].img), TX_FLOOR))
		return (1);
	if (create_image(info, &(info->texture[CE].img), info->texture[CE].path)
		&& load_xpm_image(info, &(info->texture[CE].img), TX_CEIL))
		return (1);
	if (load_xpm_image(info, &(info->texture[D].img), TX_DOOR))
		return (1);
	if (load_xpm_image(info, &(info->texture[T].img), TX_TORCH))
		return (1);
	if (load_xpm_image(info, &(info->mm_img[PLAYER]), MM_PLAYER))
		return (1);
	return (0);
}

// Load all the textures
int	load_textures(t_info *info)
{
	if (load_game_textures(info))
		return (error_msg("Couldn't load texture"));
	create_minimap(info);
	info->screen.img = mlx_new_image(info->mlx[0], W_WIDTH, W_HEIGHT);
	info->screen.addr = mlx_get_data_addr(info->screen.img,
			&(info->screen.bpp),
			&(info->screen.line_len),
			&(info->screen.endian));
	return (0);
}
