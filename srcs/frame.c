/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:40:59 by tgrivel           #+#    #+#             */
/*   Updated: 2022/11/08 13:37:02 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// For three rays, if the middle rays detect another wall than the two others,
// this rays will take the ray of the two others
static void	anti_bad(t_info *info)
{
	int	column;

	column = 0;
	if (info->ray[column + 1].wall == info->ray[column + 2].wall
		&& info->ray[column].wall != info->ray[column + 1].wall)
		info->ray[column].wall = info->ray[column + 1].wall;
	while (++column < W_WIDTH - 1)
	{
		if (info->ray[column - 1].wall == info->ray[column + 1].wall
			&& info->ray[column].wall != info->ray[column - 1].wall)
			info->ray[column].wall = info->ray[column -1].wall;
	}
	if (info->ray[column - 1].wall == info->ray[column - 2].wall
		&& info->ray[column].wall != info->ray[column - 1].wall)
		info->ray[column].wall = info->ray[column - 1].wall;
}

// Collect ray data for each column of the screen
static void	player_ray(t_info *info)
{
	int		column;

	column = 0;
	free_sprite_list(info->spriteview);
	info->spriteview = NULL;
	while (column < W_WIDTH)
	{
		angle_delta(info->player.angle + info->ray[column].angle,
			info->ray[column].delta);
		ray(info, &(info->ray[column]));
		column++;
	}
	anti_bad(info);
}

// Print infos: player position (x, y, angle)
static void	print_info(t_info *info)
{
	char	message[255];

	ft_memset(message, 0, 255);
	sprintf(message, "Position X: %f", info->player.pos[X]);
	mlx_string_put(info->mlx[INIT], info->mlx[WINDOW],
		500, 10, CO_WHITE, message);
	ft_memset(message, 0, 255);
	sprintf(message, "Position Y: %f", info->player.pos[Y]);
	mlx_string_put(info->mlx[INIT], info->mlx[WINDOW],
		500, 20, CO_WHITE, message);
	ft_memset(message, 0, 255);
	sprintf(message, "P. angle  : %f", info->player.angle);
	mlx_string_put(info->mlx[INIT], info->mlx[WINDOW],
		500, 30, CO_WHITE, message);
}

// 1. Cast rays to get view informations
// 2. Render the view screen
// 3. Print the screen
// 4. Print minimap
// 5. Print informations
void	print_frame(t_info *info)
{
	player_ray(info);
	render_screen(info);
	mlx_clear_window(info->mlx[INIT], info->mlx[WINDOW]);
	mlx_put_image_to_window(info->mlx[0], info->mlx[1], info->screen.img, 0, 0);
	if (info->active_map)
		print_minimap(info);
	print_info(info);
	mlx_put_image_to_window(info->mlx[0], info->mlx[1], info->player.pov.img,
			W_WIDTH / 4, W_HEIGHT - info->player.pov.height);
}
