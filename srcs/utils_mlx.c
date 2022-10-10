/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:46:22 by gudias            #+#    #+#             */
/*   Updated: 2022/10/10 19:30:07 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_destroy_image(void *mlx, void *img)
{
	if (img)
		mlx_destroy_image(mlx, img);
}

#ifdef __APPLE__

void	my_mouse_move(void *mlx, void *win, int x, int y)
{
	(void) mlx;
	mlx_mouse_move(win, x, y);
}

void	my_mouse_get_pos(void *mlx, void *win, int *x, int *y)
{
	(void) mlx;
	mlx_mouse_get_pos(win, x, y);
}

#else

void	my_mouse_move(void *mlx, void *win, int x, int y)
{
	mlx_mouse_move(mlx, win, x, y);
}

void	my_mouse_get_pos(void *mlx, void *win, int *x, int *y)
{
	mlx_mouse_get_pos(mlx, win, x, y);
}

#endif
