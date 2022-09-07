/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:41:17 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/09/08 00:10:58 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Calculate the delta from an angle
void	angle_delta(float angle, float *dx, float *dy)
{
	*dx = cos(angle);
	*dy = sin(angle);
}

// Calcule a distance
float	distance_pos(float ax, float ay, float bx, float by)
{
	return (sqrt(pow(bx - ax, 2) + pow(by - ay, 2)));
}
