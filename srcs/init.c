/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:44:17 by gudias            #+#    #+#             */
/*   Updated: 2022/09/10 20:49:37 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Init default value of the struct
// Init mlx
// Load the map
// Load textures
int	init_game(t_info *info, char *mapname)
{
	info->map = NULL;
	info->map_h = 0;
	info->active_map = true;
	info->player.x = -1.0f;
	info->player.dx = -1.0f;
	info->player.dy = -1.0f;
	ft_memset(&(info->texture), 0, (sizeof(t_texture)) * 6);
	info->mlx[INIT] = mlx_init();
	info->mlx[WINDOW] = 0;
	ft_memset(&(info->mm_img), 0, (sizeof(void *) * 3));
	if (!info->mlx[INIT])
		return (error_msg("Couldn't init mlx"));
	if (load_map(info, mapname) || load_textures(info))
		return (1);
	return (0);
}
