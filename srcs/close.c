/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:45:50 by gudias            #+#    #+#             */
/*   Updated: 2022/09/06 10:32:37 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_images(t_info *info)
{
	my_destroy_image(info->mlx[INIT], info->mm_img[GROUND]);
	my_destroy_image(info->mlx[INIT], info->mm_img[WALL]);
	my_destroy_image(info->mlx[INIT], info->mm_img[PLAYER]);
	my_destroy_image(info->mlx[INIT], info->texture[NO].img);
	my_destroy_image(info->mlx[INIT], info->texture[SO].img);
	my_destroy_image(info->mlx[INIT], info->texture[EA].img);
	my_destroy_image(info->mlx[INIT], info->texture[WE].img);
	my_destroy_image(info->mlx[INIT], info->texture[FL].img);
	my_destroy_image(info->mlx[INIT], info->texture[CE].img);
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

// Usage:
// if str = "ppt"
// p is a simple pointer to free
// t is a table pointer to free
void	va_free(char *str, ...)
{
	va_list	arg;

	va_start(arg, str);
	while (*str)
	{
		if (*str == 'p')
			free(va_arg(arg, char *));
		if (*str == 't')
			free_array(va_arg(arg, char **));
		++str;
	}
	va_end(arg);
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
