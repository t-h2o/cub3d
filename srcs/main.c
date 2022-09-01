/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:47:21 by gudias            #+#    #+#             */
/*   Updated: 2022/08/31 18:34:20 by gudias           ###   ########.fr       */
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

	if (init_game(&info))
		return (1);

	if (load_map(&info, av[1]))
		return (1);
	
	//print map informations
	printf("NO: %s\nSO: %s\nEA: %s\nWE: %s\nF: %s\nC: %s\n", info.texture.north, info.texture.south, info.texture.east, info.texture.west, info.texture.floor, info.texture.ceil);
	
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
	if (start_window(&info))
		return (1);
	return (0);
}
