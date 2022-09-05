/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:51:07 by gudias            #+#    #+#             */
/*   Updated: 2022/09/05 18:42:21 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// HEADERS

# include	<stdio.h>
# include	<fcntl.h>
# include	<math.h>
# include	"keys.h"
# include	"../libs/libft/includes/libft.h"

# ifdef __APPLE__
#  include	"../libs/mlx-apple/mlx.h"

# elif __linux__
#  include	"../libs/mlx-linux/mlx.h"
#  include	"../libs/mlx-linux/mlx_int.h"

# endif

// Define

// Path for textures
// minimap textures
# define MM_GROUND	"assets/textures/minimap/ground.xpm"
# define MM_WALL	"assets/textures/minimap/wall.xpm"
# define MM_PLAYER	"assets/textures/minimap/player.xpm"

// game textures
# define TX_NORTH	"assets/textures/default_north.xpm"
# define TX_SOUTH	"assets/textures/default_south.xpm"
# define TX_EAST	"assets/textures/default_east.xpm"
# define TX_WEST	"assets/textures/default_west.xpm"
# define TX_FLOOR	"assets/textures/default_floor.xpm"
# define TX_CEIL	"assets/textures/default_ceil.xpm"

# define MAPSDIR	"assets/maps/"

// Color
# define CO_WHITE		0x00FFFFFF

// Sensibility
//   rotation = (PI / 8)
# define PS_MOVE		1.0f
# define PS_ROTATE	0.392699081699f

// Window size [px]
# define W_WIDTH	1024
# define W_HEIGHT	768

// Location of the Minimap from the top left corner
# define MM_POS_Y	10
# define MM_POS_X	10

// Size of a square of the mini map
# define MM_SIZE_TILE	10
# define MM_SIZE_PLAYER	4

// Structure

// Mlx pointer for the window
enum e_mlx {
	INIT,
	WINDOW
};

// Mini map texture
enum e_mm {
	GROUND,
	WALL,
	PLAYER
};

enum e_tx {
	NO,
	SO,
	EA,
	WE,
	FL,
	CE
};

// data struct to draw into an image
typedef struct s_img_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

// Store all the textures informations:
// - the path to the texture
// - the pointer to the image
typedef struct s_texture {
	char	*path;
	void	*img;
}	t_texture;

typedef struct s_player {
	float	x;
	float	y;
	float	angle;
	float	dx;
	float	dy;
}	t_player;

// mlx: pointer on informations of the window
typedef struct s_info {
	void		*mlx[2];
	char		**map;
	void		*mm_img[3];
	int			map_h;
	t_player	player;
	t_texture	texture[6];
}	t_info;

// check_map.c
int		check_extension(char *mapname);
int		check_map_data(t_info *info);

//close.c
void	free_array(char **array);
int		error_msg(char *msg);
void	exit_error(char *msg);
int		close_game(t_info *info);

// parsing.c
int		load_map(t_info *info, char *mapname);

// init.c
int		init_game(t_info *info, char *mapname);

// mini_map.c
void	print_minimap(t_info *info);

// parse_utils.c
char	*skip_whitespaces(char *str);
int		convert_rgb(char *rgb);

// player.c
void	player_move(t_info *info, float distance);
void	player_rotate(t_info *info, float rotation);

// textures.c
int	load_textures(t_info *info);

// window.c
int		start_window(t_info *info);

#endif /* CUB3D_H */
