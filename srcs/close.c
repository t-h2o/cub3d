/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 17:45:50 by gudias            #+#    #+#             */
/*   Updated: 2022/08/23 13:06:35 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

int		error_msg(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	return (1);
}

void	exit_error(char *msg)
{
	exit(error_msg(msg));
}
