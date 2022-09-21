/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:51:07 by gudias            #+#    #+#             */
/*   Updated: 2022/09/15 14:13:18 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// HEADERS

# include	<stdio.h>
# include	<stdbool.h>
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
# define CO_BLUE		0x00000070

// Sensibility
//   rotation = (PI / 8)
# define PS_MOVE	0.5f
# define PS_ROTATE	0.392699081699f

// Field of view ~70 degrees
# define FOV		1.2f

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

enum e_axis {
	X,
	Y,
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
	float	pos[2];
	float	angle;
	float	delta[2];
}	t_player;

// distance between the player and the wall
// wall: NEWS
typedef struct s_ray {
	float	angle;
	float	delta[2];
	float	hit[2];
	float	distance;
	char	wall;
}	t_ray;

// mlx: pointer on informations of the window
typedef struct s_info {
	void		*mlx[2];
	char		**map;
	void		*mm_img[3];
	int			map_h;
	t_player	player;
	t_texture	texture[6];
	bool		active_map;
	t_ray		ray[1024];
}	t_info;

// check_map.c
int		check_extension(char *mapname);
int		check_map_data(t_info *info);

// close.c
void	free_array(char **array);
int		error_msg(char *msg);
void	close_game(t_info *info, int exit_code);

// init.c
int		init_game(t_info *info, char *mapname);

// frame.c
void	print_frame(t_info *info);

// mini_map.c
void	print_minimap(t_info *info);

// parsing.c
int		load_map(t_info *info, char *mapname);

// player.c
void	player_move(t_info *info, float distance);
void	player_rotate(t_info *info, float rotation);

// ray.c
void	player_ray(t_info *info);

// textures.c
int		load_textures(t_info *info);

// utils_math.c
void	angle_delta(float angle, float delta[2]);
float	angle_sum(float angle_a, float angle_b);
float	sqrt_points(float o[2], float d[2]);

// utils_mlx.c
void	my_destroy_image(void *mlx, void *img);

// utils_parsing.c
char	*skip_whitespaces(char *str);
int		convert_rgb(char *rgb);

// utils_rays.c
float	horizontal_up(t_info *info, float hit[2], float delta[2]);
float	horizontal_down(t_info *info, float hit[2], float delta[2]);
float	vertical_right(t_info *info, float hit[2], float delta[2]);
float	vertical_left(t_info *info, float hit[2], float delta[2]);

// window.c
int		start_window(t_info *info);

#endif /* CUB3D_H */
