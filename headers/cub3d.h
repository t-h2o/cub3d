/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:51:07 by gudias            #+#    #+#             */
/*   Updated: 2022/08/26 16:17:29 by tgrivel          ###   ########.fr       */
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

// Path for texture of mini map
# define PMM_EMPTY	"assets/mini_map/empty.xpm"
# define PMM_WALL	"assets/mini_map/wall.xpm"

# define MAPSDIR	"assets/maps/"
# define W_WIDTH	1024
# define W_HEIGHT	768

// Location of the Minimap from the top left
# define MM_TOP		10
# define MM_LEFT	10

// Size of sqare of mini map
# define MM_SQUARE	10

// STRUCTURE

enum e_mlx {
	INIT,
	WINDOW
};

// Mini map texture
enum e_mm {
	EMPTY,
	WALL
};

// mlx: pointer on informations of the window
typedef struct s_info {
	void	*mlx[2];
	char	**map;
	void	*mm[2];
	int		map_h;
}	t_info;

//close.c
void	free_map(char **map);
int		error_msg(char *msg);
void	exit_error(char *msg);

// get_map.c
int		get_map(t_info *info, char *mapname);

// init.c
int		init_game(t_info *info);

// window.c
int		start_window(t_info *info);

#endif /* CUB3D_H */
