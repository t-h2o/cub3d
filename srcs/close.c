/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:45:50 by gudias            #+#    #+#             */
/*   Updated: 2022/08/28 09:06:13 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_images(t_info *info)
{
	mlx_destroy_image(info->mlx[INIT], info->mm_img[GROUND]);
	mlx_destroy_image(info->mlx[INIT], info->mm_img[WALL]);
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
