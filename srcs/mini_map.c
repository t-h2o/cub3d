/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 12:16:47 by user42            #+#    #+#             */
/*   Updated: 2022/09/07 22:31:48 by melogr@phy       ###   ########.fr       */
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
}

static void	print_player(t_info *info)
{
	mlx_put_image_to_window(info->mlx[0], info->mlx[1],
		info->mm_img[PLAYER],
		MM_POS_X + info->player.x * MM_SIZE_TILE - MM_SIZE_PLAYER / 2,
		MM_POS_Y + info->player.y * MM_SIZE_TILE - MM_SIZE_PLAYER / 2);
}

// Position player
static void	print_info(t_info *info)
{
	char	*tmp;
	char	*itoa;

	itoa = ft_itoa((int)info->player.x);
	tmp = ft_strjoin("Position X: ", itoa);
	free(itoa);
	mlx_string_put(info->mlx[INIT], info->mlx[WINDOW], 500, 10, CO_WHITE, tmp);
	free(tmp);
	itoa = ft_itoa((int)info->player.y);
	tmp = ft_strjoin("Position Y: ", itoa);
	free(itoa);
	mlx_string_put(info->mlx[INIT], info->mlx[WINDOW], 500, 20, CO_WHITE, tmp);
	free(tmp);
	itoa = ft_itoa((int)info->player.angle);
	tmp = ft_strjoin("    Angle : ", itoa);
	free(itoa);
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
	player_ray(info);
	print_info(info);
}
