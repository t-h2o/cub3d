/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:16:47 by user42            #+#    #+#             */
/*   Updated: 2022/09/01 14:57:19 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Print the texture chosen with the char of the map
// Position:
//   x: Size * x_char + distance from the left
//   y: Size * y_char + distance from the top
// Get player position:
//   x: Size * x_char + ((SQUARE_MAP - SQUARE_PLAYER) / 2)
//   y: Size * y_char + ((SQUARE_MAP - SQUARE_PLAYER) / 2)
static void	print_square(t_info *info, char c, int y, int x)
{
	if (c == '0' || c == 'N' || c == 'E' || c == 'S' || c == 'W')
		mlx_put_image_to_window(info->mlx[0], info->mlx[1],
			info->mm_img[GROUND],
			x * MM_SIZE_TILE + MM_POS_X,
			y * MM_SIZE_TILE + MM_POS_Y);
	if (c == '1')
		mlx_put_image_to_window(info->mlx[0], info->mlx[1],
			info->mm_img[WALL],
			x * MM_SIZE_TILE + MM_POS_X,
			y * MM_SIZE_TILE + MM_POS_Y);
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		if (info->player.x == -1.0f)
		{
			info->player.x = (float)(x * MM_SIZE_TILE)
				+ ((MM_SIZE_TILE - MM_SIZE_PLAYER) / 2);
			info->player.y = (float)(y * MM_SIZE_TILE)
				+ ((MM_SIZE_TILE - MM_SIZE_PLAYER) / 2);
			info->player.angle = 0.0f;
		}
	}
}

static void	print_player(t_info *info)
{
	mlx_put_image_to_window(info->mlx[0], info->mlx[1],
		info->mm_img[PLAYER],
		MM_POS_X + info->player.x,
		MM_POS_Y + info->player.y);
}

// Position player
static void	print_info(t_info *info)
{
	char	*tmp;

	tmp = ft_strjoin("Position X: ", ft_itoa((int)info->player.x));
	mlx_string_put(info->mlx[INIT], info->mlx[WINDOW], 500, 10, CO_WHITE, tmp);
	free(tmp);
	tmp = ft_strjoin("Position Y: ", ft_itoa((int)info->player.y));
	mlx_string_put(info->mlx[INIT], info->mlx[WINDOW], 500, 20, CO_WHITE, tmp);
	free(tmp);
	tmp = ft_strjoin("    Angle : ", ft_itoa((int)info->player.angle));
	mlx_string_put(info->mlx[INIT], info->mlx[WINDOW], 500, 30, CO_WHITE, tmp);
	free(tmp);
}

// Clear the window
// Print the mini map
// Print the player
// Print the data
void	print_minimap(t_info *info)
{
	int		pos_x;
	int		pos_y;

	mlx_clear_window
		(info->mlx[INIT], info->mlx[WINDOW]);
	pos_y = -1;
	while (info->map[++pos_y])
	{
		pos_x = -1;
		while (info->map[pos_y][++pos_x])
			print_square(info, info->map[pos_y][pos_x], pos_y, pos_x);
	}
	print_player(info);
	print_info(info);
}
