/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:45:50 by gudias            #+#    #+#             */
/*   Updated: 2022/09/01 17:54:57 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_images(t_info *info)
{
	mlx_destroy_image(info->mlx[INIT], info->mm_img[GROUND]);
	mlx_destroy_image(info->mlx[INIT], info->mm_img[WALL]);
	mlx_destroy_image(info->mlx[INIT], info->mm_img[PLAYER]);

	free(info->texture.north);
	free(info->texture.south);
	free(info->texture.east);
	free(info->texture.west);
	free(info->texture.floor);
	free(info->texture.ceil);

	mlx_destroy_image(info->mlx[INIT], info->texture.img_north);
	mlx_destroy_image(info->mlx[INIT], info->texture.img_south);
	mlx_destroy_image(info->mlx[INIT], info->texture.img_east);
	mlx_destroy_image(info->mlx[INIT], info->texture.img_west);
	//mlx_destroy_image(info->mlx[INIT], info->texture.img_floor);
	//mlx_destroy_image(info->mlx[INIT], info->texture.img_ceil);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

int	error_msg(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	return (1);
}

void	exit_error(char *msg)
{
	exit(error_msg(msg));
}

int	close_game(t_info *info)
{
	free_map(info->map);
	mlx_destroy_window(info->mlx[INIT], info->mlx[WINDOW]);
	destroy_images(info);
	exit(0);
	return (0);
}
