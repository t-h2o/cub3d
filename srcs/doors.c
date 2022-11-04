/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 18:21:52 by gudias            #+#    #+#             */
/*   Updated: 2022/10/07 20:10:41 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Check doors error
//  not at map extremity
//  surrounded by wall (vertical or horizontal)
int	check_doors(t_info *info, int y)
{
	int	x;

	x = -1;
	while (info->map[y][++x] && info->map[y][x] != '\n')
	{
		if (info->map[y][x] == 'D')
		{
			if (x == 0 || x >= (int) ft_strlen(info->map[y]) - 2 || y == 0
				|| y == info->mapsize[Y] - 1 || (info->map[y][x + 1] == '0'
				&& (info->map[y][x - 1] != '0'
				|| info->map[y + 1][x] != '1' || info->map[y - 1][x] != '1'))
				|| (info->map[y][x + 1] == '1' && (info->map[y][x - 1] != '1'
				|| info->map[y + 1][x] != '0' || info->map[y - 1][x] != '0')))
				return (error_msg("Invalid door position"));
		}
	}
	return (0);
}
