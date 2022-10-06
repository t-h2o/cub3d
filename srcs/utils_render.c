/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:54:39 by gudias            #+#    #+#             */
/*   Updated: 2022/10/06 19:52:08 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	calc_x_scaling(t_ray *ray)
{
	if (ray->wall == NO || ray->wall == SO)
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
