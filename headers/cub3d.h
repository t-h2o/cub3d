/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:51:07 by gudias            #+#    #+#             */
/*   Updated: 2022/08/27 17:28:27 by gudias           ###   ########.fr       */
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

// Path for textures
# define MM_GROUND	"assets/textures/minimap/ground.xpm"
# define MM_WALL	"assets/textures/minimap/wall.xpm"

# define MAPSDIR	"assets/maps/"

// Window size [px]
# define W_WIDTH	1024
# define W_HEIGHT	768

// Location of the Minimap from the top left corner
# define MM_POS_Y	10
# define MM_POS_X	10

// Size of a square of the mini map
# define MM_TILESIZE	10 

// STRUCTURE

// Mlx pointer for the window
enum e_mlx {
	INIT,
	WINDOW
};

// Mini map texture
enum e_mm {
	GROUND,
	WALL
};

// mlx: pointer on informations of the window
typedef struct s_info {
	void	*mlx[2];
	char	**map;
	void	*mm_img[2];
	int		map_h;
}	t_info;

//close.c
void	free_map(char **map);
int		error_msg(char *msg);
void	exit_error(char *msg);
int 	close_game(t_info *info);

// mini_map.c

void	print_minimap(t_info *info);

// get_map.c
int		get_map(t_info *info, char *mapname);

// init.c
int		init_game(t_info *info);

// window.c
int		start_window(t_info *info);
void		destroy_window(t_info *info);

#endif /* CUB3D_H */
