/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:47:21 by gudias            #+#    #+#             */
/*   Updated: 2022/08/22 16:21:03 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	main(int ac, char **av)
{
	t_info	info;
	t_game	game;
	
	ft_putstr("Cub3D\n");
	
	if (ac != 2)
		exit_error("Invalid argument");

	if (start_window(&info))
		return (1);
	
	init_game(&game);

	get_map(&game, av[1]);

	//print the map	
	if (game.map)
	{
		int i = 0;
		while (game.map[i])
		{
			ft_printf("%s", game.map[i]);
			i++;
		}	
	}

	free_map(game.map);	
	return (0);
}
