/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:50:53 by gudias            #+#    #+#             */
/*   Updated: 2022/09/21 23:47:43 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

void	render_screen(t_info *info)
{
	int		column;
	int		wall_height;
	int		wall_offset;
	char	*dst;
	int		line;
	int		color;

	column = -1;
	while (++column < W_WIDTH)
	{
		line = -1;
		while (++line < W_HEIGHT)
		{
			dst = info->screen.addr + (line * info->screen.line_length) + (column * info->screen.bits_per_pixel / 8);
		   *(unsigned int *)dst = 0xFF000000;
		}

		wall_height = (W_HEIGHT * 1.2f ) / info->ray[column].distance;
		if (wall_height > W_HEIGHT)
			wall_height = W_HEIGHT;
		wall_offset = (W_HEIGHT / 2) - (wall_height >> 1);

		if (info->ray[column].wall == 'N')
			color = CO_YELLOW;
		else if(info->ray[column].wall == 'S')
			color = CO_RED;
		else if(info->ray[column].wall == 'W')
			color = CO_GREEN;
		else if(info->ray[column].wall == 'E')
			color = CO_BLUE;
		dst = info->screen.addr + (wall_offset * info->screen.line_length)
			+ (column * info->screen.bits_per_pixel / 8);
		while (wall_height--)
		{
			*(unsigned int *)dst = color;
			dst += info->screen.line_length;
		}

		//top wall line
		//dst = info->screen.addr + (wall_offset * info->screen.line_length)
		//	+ (column * info->screen.bits_per_pixel / 8);
		//mlx_pixel_put(info->mlx[0], info->mlx[1],
		//		column, wall_offset, CO_WHITE);
		//bot wall line
		//dst += (wall_height * info->screen.line_length);
		//*(unsigned int *)dst = CO_WHITE;
		//mlx_pixel_put(info->mlx[0], info->mlx[1],
		//		column, wall_offset + wall_height, CO_BLUE);
	}
}
