/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:41:17 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/09/13 11:06:14 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Calculate the delta from an angle
void	angle_delta(float angle, float *dx, float *dy)
{
	*dx = cos(angle);
	*dy = sin(angle);
}

// return the sum of angle A and angle B
float	angle_sum(float angle_a, float angle_b)
{
	float	sum;

	sum = angle_a + angle_b;
	if (sum < 0)
		sum += 2 * M_PI;
	if (2 * M_PI < sum)
		sum -= 2 * M_PI;
	return (sum);
}

// Origin (x, y) to Destination (x, y)
float	sqrt_points(float ox, float oy, float dx, float dy)
{
	return (sqrt(pow(dx - ox, 2) + pow(dy - oy, 2)));
}
