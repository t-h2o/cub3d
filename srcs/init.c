/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:44:17 by gudias            #+#    #+#             */
/*   Updated: 2022/09/10 23:01:16 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Init the angle of the ray
static void	init_ray(t_info *info)
{
	int		column;

	column = -1;
	while (++column < W_WIDTH)
		info->ray[column].angle = FOV
			* ((float)column / (float)(W_WIDTH - 1) - 0.5f);
}

// Init default value of the struct
// Init mlx
// Load the map
// Load textures
int	init_game(t_info *info, char *mapname)
{
	ft_memset(info, 0, (sizeof(t_info)));
	info->active_map = true;
	info->player.pos[X] = -1.0f;
	info->player.delta[X] = -1.0f;
	info->player.delta[Y] = -1.0f;
	init_ray(info);
	if (load_map(info, mapname))
		return (1);
	info->mlx[INIT] = mlx_init();
	if (!info->mlx[INIT])
		return (error_msg("Couldn't init mlx"));
	if (load_textures(info))
		return (1);
	return (0);
}
