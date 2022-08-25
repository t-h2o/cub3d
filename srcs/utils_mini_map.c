/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mini_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:32:49 by user42            #+#    #+#             */
/*   Updated: 2022/08/25 21:34:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Load texture for the minimap
int	load_texture(t_info *info)
{
	int		img_width;
	int		img_height;

	info->mm[SPACE] = mlx_xpm_file_to_image
		(info->mlx[INIT], PMM_SPACE, &img_width, &img_height);
	info->mm[EMPTY] = mlx_xpm_file_to_image
		(info->mlx[INIT], PMM_EMPTY, &img_width, &img_height);
	info->mm[WALL] = mlx_xpm_file_to_image
		(info->mlx[INIT], PMM_WALL, &img_width, &img_height);
	return (0);
}
