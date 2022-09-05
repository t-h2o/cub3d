/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:45:50 by gudias            #+#    #+#             */
/*   Updated: 2022/09/05 01:34:04 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_images(t_info *info)
{
	if (info->mm_img[GROUND])
		mlx_destroy_image(info->mlx[INIT], info->mm_img[GROUND]);
	if (info->mm_img[WALL])
		mlx_destroy_image(info->mlx[INIT], info->mm_img[WALL]);
	if (info->mm_img[PLAYER])
		mlx_destroy_image(info->mlx[INIT], info->mm_img[PLAYER]);
	if (info->texture[NO].img)
		mlx_destroy_image(info->mlx[INIT], info->texture[NO].img);
	if (info->texture[SO].img)
		mlx_destroy_image(info->mlx[INIT], info->texture[SO].img);
	if (info->texture[EA].img)
		mlx_destroy_image(info->mlx[INIT], info->texture[EA].img);
	if (info->texture[WE].img)
		mlx_destroy_image(info->mlx[INIT], info->texture[WE].img);
	if (info->texture[FL].img)
		mlx_destroy_image(info->mlx[INIT], info->texture[FL].img);
	if (info->texture[CE].img)
		mlx_destroy_image(info->mlx[INIT], info->texture[CE].img);
}

static void	free_textures_path(t_info *info)
{
	if (info->texture[NO].path)
		free(info->texture[NO].path);
	if (info->texture[SO].path)
		free(info->texture[SO].path);
	if (info->texture[EA].path)
		free(info->texture[EA].path);
	if (info->texture[WE].path)
		free(info->texture[WE].path);
	if (info->texture[FL].path)
		free(info->texture[FL].path);
	if (info->texture[CE].path)
		free(info->texture[CE].path);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

int	error_msg(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	return (1);
}

int	close_game(t_info *info)
{
	free_array(info->map);
	if (info->mlx[WINDOW])
		mlx_destroy_window(info->mlx[INIT], info->mlx[WINDOW]);
	destroy_images(info);
	free_textures_path(info);
	exit(0);
	return (0);
}
