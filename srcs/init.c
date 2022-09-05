/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:44:17 by gudias            #+#    #+#             */
/*   Updated: 2022/09/05 23:31:44 by melogr@phy       ###   ########.fr       */
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
	info->player.x = -1.0f;
	info->texture[NO].path = NULL;
	info->texture[SO].path = NULL;
	info->texture[EA].path = NULL;
	info->texture[WE].path = NULL;
	info->texture[FL].path = NULL;
	info->texture[CE].path = NULL;
	info->texture[NO].img = NULL;
	info->texture[SO].img = NULL;
	info->texture[EA].img = NULL;
	info->texture[WE].img = NULL;
	info->texture[FL].img = NULL;
	info->texture[CE].img = NULL;
	info->mlx[INIT] = mlx_init();
	info->mlx[WINDOW] = 0;
	ft_memset(&(info->mm_img), 0, (sizeof(void *) * 3));
	if (!info->mlx[INIT])
		return (error_msg("Couldn't init mlx"));
	if (load_map(info, mapname) || load_textures(info))
		return (1);
	return (0);
}
