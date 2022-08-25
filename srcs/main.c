/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:47:21 by gudias            #+#    #+#             */
/*   Updated: 2022/08/25 14:36:34 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	main(int ac, char **av)
{
	t_info	info;
	int		i;

	ft_putstr("Cub3D\n");

	if (ac != 2)
		exit_error("Invalid argument");

	init_game(&info);

	if (get_map(&info, av[1]))
		return (1);

	//print the map	
	if (info.map)
	{
		i = 0;
		while (info.map[i])
		{
			ft_printf("%s", info.map[i]);
			i++;
		}
	}
	free_map(info.map);

	if (start_window(&info))
		return (1);

	return (0);
}
