/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrivel <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:08:43 by tgrivel           #+#    #+#             */
/*   Updated: 2022/09/13 16:03:04 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

// Size of the wall = A * distance + B
#define A	-50
#define B	300

// Distance between column [pixel]
#define N	30

static void	draw_column(t_info *info, int column, float distance, int color)
{
	float	size_wall;
	int		pixy;
	float	middle;

	middle = W_HEIGHT / 2;
	size_wall = A * distance + B;
	pixy = middle - size_wall / 2;
	while (pixy < middle + size_wall / 2)
	{
		mlx_pixel_put(info->mlx[INIT], info->mlx[WINDOW],
			column,
			pixy++,
			color);
	}
}

//		distance = distance * cos((column - W_WIDTH / 2) * FOV); 
void	render(t_info *info)
{
	int		column;
	int		color;
	float	distance;

	column = -1;
	while (column < W_WIDTH)
	{
		distance = info->ray[column].distance;
		if (info->ray[column].wall == 'N')
			color = CO_RED;
		if (info->ray[column].wall == 'E')
			color = CO_GREEN;
		if (info->ray[column].wall == 'S')
			color = CO_BLUE;
		if (info->ray[column].wall == 'W')
			color = CO_RAN;
		draw_column(info, column, distance, color);
		column += N;
	}
}
