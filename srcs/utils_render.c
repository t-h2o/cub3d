/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:54:39 by gudias            #+#    #+#             */
/*   Updated: 2022/11/07 17:59:31 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	calc_x_scaling(t_ray *ray)
{
	if (ray->hitdir)
		return (ray->hit[X] - (int)ray->hit[X]);
	else
		return (ray->hit[Y] - (int)ray->hit[Y]);
}

void	add_shade(char *dst, float distance)
{
	float		shading;

	if (distance <= FOG_MIN)
		return ;
	shading = 1 / (distance - FOG_MIN + 1);
	dst[0] = (unsigned char)dst[0] * shading;
	dst[1] = (unsigned char)dst[1] * shading;
	dst[2] = (unsigned char)dst[2] * shading;
}

void	draw_crosshair(t_info *info)
{
	char	*h_dst;
	char	*v_dst;
	int		i;

	h_dst = info->screen.addr + ((W_HEIGHT / 2) * info->screen.line_len)
		+ (((W_WIDTH / 2) - CROSSHAIR_SIZE - (CROSSHAIR_GAP / 2))
			* info->screen.bpp / 8);
	v_dst = info->screen.addr + ((W_WIDTH / 2) * info->screen.bpp / 8)
		+ (((W_HEIGHT / 2) - CROSSHAIR_SIZE - (CROSSHAIR_GAP / 2))
			* info->screen.line_len);
	i = -1;
	while (++i < CROSSHAIR_SIZE)
	{
		*(unsigned int *)h_dst = CROSSHAIR_COLOR;
		*(unsigned int *)(h_dst + (CROSSHAIR_SIZE + CROSSHAIR_GAP)
				* (info->screen.bpp / 8)) = CROSSHAIR_COLOR;
		*(unsigned int *)v_dst = CROSSHAIR_COLOR;
		*(unsigned int *)(v_dst + (CROSSHAIR_SIZE + CROSSHAIR_GAP)
				* info->screen.line_len) = CROSSHAIR_COLOR;
		h_dst += info->screen.bpp / 8;
		v_dst += info->screen.line_len;
	}
}
