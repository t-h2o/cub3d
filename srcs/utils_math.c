/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 21:41:17 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/09/12 16:45:37 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Calculate the delta from an angle
void	angle_delta(float angle, float delta[2])
{
	delta[X] = cos(angle);
	delta[Y] = sin(angle);
}

// return the sum of angle A and angle B
float	angle_sum(float angle_a, float angle_b)
{
	float	sum;

	sum = angle_a + angle_b;
	while (sum < 0)
		sum += 2 * M_PI;
	while (2 * M_PI < sum)
		sum -= 2 * M_PI;
	return (sum);
}
