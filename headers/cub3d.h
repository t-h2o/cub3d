/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:51:07 by gudias            #+#    #+#             */
/*   Updated: 2022/08/22 15:47:02 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// HEADERS

# include	<stdio.h>
# include	<fcntl.h>
# include	"keys.h"
# include	"../libs/libft/includes/libft.h"

# ifdef __APPLE__
#  include	"../libs/mlx-apple/mlx.h"

# elif __linux__
#  include	"../libs/mlx-linux/mlx.h"
#  include	"../libs/mlx-linux/mlx_int.h"

# endif

// DEFINE

# define MAPSDIR	"./assets/maps/"
# define W_WIDTH	1024
# define W_HEIGHT	768

// STRUCTURE

enum e_mlx {
	INIT,
	WINDOW
};

// mlx: pointer on informations of the window
typedef struct s_info {
	void	*mlx[2];
}	t_info;

//check_map
int	check_extension(char *mapname);

//get_map
char	**get_map(char *mapname);

// window.c
int		start_window(t_info *info);

#endif /* CUB3D_H */
