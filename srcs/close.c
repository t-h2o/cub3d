/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:45:50 by gudias            #+#    #+#             */
/*   Updated: 2022/09/04 15:38:47 by gudias           ###   ########.fr       */
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
	if (info->texture.north)
		free(info->texture.north);
	if (info->texture.south)
		free(info->texture.south);
	if (info->texture.east)
		free(info->texture.east);
	if (info->texture.west)
		free(info->texture.west);
	if (info->texture.floor)
		free(info->texture.floor);
	if (info->texture.ceil)
		free(info->texture.ceil);
	if (info->texture.img_north)
		mlx_destroy_image(info->mlx[INIT], info->texture.img_north);
	if (info->texture.img_south)
		mlx_destroy_image(info->mlx[INIT], info->texture.img_south);
	if (info->texture.img_east)
		mlx_destroy_image(info->mlx[INIT], info->texture.img_east);
	if (info->texture.img_west)
		mlx_destroy_image(info->mlx[INIT], info->texture.img_west);
	if (info->texture.img_floor)
		mlx_destroy_image(info->mlx[INIT], info->texture.img_floor);
	if (info->texture.img_ceil)
		mlx_destroy_image(info->mlx[INIT], info->texture.img_ceil);
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
	exit(0);
	return (0);
}
