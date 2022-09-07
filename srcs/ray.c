/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:04:24 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/07 22:31:12 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Print random ray
// ind: index
// ray_x: where the player is locate
static void	ray(t_info *info, float dx, float dy)
{
	float	ray_x;
	float	ray_y;

	ray_x = info->player.x;
	ray_y = info->player.y;
	while (info->map[(int)(ray_y)][(int)(ray_x)] != '1')
	{
		mlx_pixel_put(info->mlx[INIT], info->mlx[WINDOW],
			ray_x * MM_SIZE_TILE + MM_POS_X,
			ray_y * MM_SIZE_TILE + MM_POS_Y,
			CO_BLUE);
		ray_x += dx / MM_SIZE_TILE;
		ray_y += dy / MM_SIZE_TILE;
	}
}

void	player_ray(t_info *info)
{
	ray(info, info->player.dx, info->player.dy);
}
