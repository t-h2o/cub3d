/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:47:21 by gudias            #+#    #+#             */
/*   Updated: 2022/08/23 21:53:17 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	main(int ac, char **av)
{
	t_info	info;
	t_game	game;
	int		i;

	ft_putstr("Cub3D\n");

	if (ac != 2)
		exit_error("Invalid argument");

	init_game(&game);

	if (get_map(&game, av[1]))
		return (1);

	//print the map	
	if (game.map)
	{
		i = 0;
		while (game.map[i])
		{
			ft_printf("%s", game.map[i]);
			i++;
		}
	}
	free_map(game.map);

	if (start_window(&info))
		return (1);

	return (0);
}
