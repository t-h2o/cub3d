/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:45:50 by gudias            #+#    #+#             */
/*   Updated: 2022/11/08 13:36:46 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_images(t_info *info)
{
	my_destroy_image(info->mlx[INIT], info->mm_img[MAP].img);
	my_destroy_image(info->mlx[INIT], info->mm_img[PLAYER].img);
	my_destroy_image(info->mlx[INIT], info->texture[NO].img.img);
	my_destroy_image(info->mlx[INIT], info->texture[SO].img.img);
	my_destroy_image(info->mlx[INIT], info->texture[EA].img.img);
	my_destroy_image(info->mlx[INIT], info->texture[WE].img.img);
	my_destroy_image(info->mlx[INIT], info->texture[FL].img.img);
	my_destroy_image(info->mlx[INIT], info->texture[CE].img.img);
	my_destroy_image(info->mlx[INIT], info->texture[D].img.img);
	my_destroy_image(info->mlx[INIT], info->texture[T1].img.img);
	my_destroy_image(info->mlx[INIT], info->texture[T2].img.img);
	my_destroy_image(info->mlx[INIT], info->texture[T3].img.img);
	my_destroy_image(info->mlx[INIT], info->texture[PISTOL1].img.img);
	my_destroy_image(info->mlx[INIT], info->player.pov.img);
}

static void	free_textures_path(t_info *info)
{
	free(info->texture[NO].path);
	free(info->texture[SO].path);
	free(info->texture[EA].path);
	free(info->texture[WE].path);
	free(info->texture[FL].path);
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

void	close_game(t_info *info, int exit_code)
{
	free_array(info->map);
	if (info->mlx[WINDOW])
		mlx_destroy_window(info->mlx[INIT], info->mlx[WINDOW]);
	destroy_images(info);
	free_textures_path(info);
	exit(exit_code);
}
