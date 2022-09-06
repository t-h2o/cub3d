/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:47:21 by gudias            #+#    #+#             */
/*   Updated: 2022/09/05 23:36:45 by melogr@phy       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	main(int ac, char **av)
{
	t_info	info;
	int		i;

	ft_putstr("Cub3D\n");

	if (ac != 2)
		exit(error_msg("Invalid argument"));

	if (init_game(&info, av[1]))
		close_game(&info, 1);
	
	//print map informations
	printf("NO: %s\nSO: %s\nEA: %s\nWE: %s\nF: %s\nC: %s\n", info.texture[NO].path, info.texture[SO].path, info.texture[EA].path, info.texture[WE].path, info.texture[FL].path, info.texture[CE].path);
	
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
		close_game(&info, 1);
	return (0);
}
