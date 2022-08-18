/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:47:21 by gudias            #+#    #+#             */
/*   Updated: 2022/08/22 15:40:17 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"

int	main(int ac, char **av)
{
	t_info	info;
	char	**map;

	if (ac != 2)
	{
		ft_printf("Error: invalid argument\n");
		return (1);
	}

	ft_putstr("Cub3D\n");
	if (start_window(&info))
		return (1);

	map = get_map(av[1]);
	if (map)
		ft_printf("%p\n", map);
	else
		ft_printf("map error\n");
	
	return (0);
}
