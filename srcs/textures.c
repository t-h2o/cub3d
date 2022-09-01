/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:02:07 by gudias            #+#    #+#             */
/*   Updated: 2022/09/01 18:08:04 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_default_textures(t_info *info)
{
	if (!info->texture.north)
		info->texture.north = TX_NORTH;
	if (!info->texture.south)
		info->texture.south = TX_SOUTH;
	if (!info->texture.east)
		info->texture.east = TX_EAST;
	if (!info->texture.west)
		info->texture.west = TX_WEST;
	if (!info->texture.floor)
		info->texture.north = TX_FLOOR;
	if (!info->texture.ceil)
		info->texture.ceil = TX_CEIL;
}
