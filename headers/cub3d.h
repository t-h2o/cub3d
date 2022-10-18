/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:51:07 by gudias            #+#    #+#             */
/*   Updated: 2022/11/07 17:36:33 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// LIBS
# include	<stdio.h>
# include	<stdbool.h>
# include	<fcntl.h>
# include	<math.h>
# include	<libft.h>
# include	<mlx.h>

// HEADERS FILES
# include	"keys.h"
# include	"textures.h"
# include	"color.h"

// GAME SETTINGS

// Maps directory
# define MAPSDIR	"assets/maps/"

// Window size [px]
# define W_WIDTH	1024
# define W_HEIGHT	768

// Field of view ~70 degrees
# define FOV		1.2f

// Player settings
//   player movement speed
//   player rotation = (2PI / 128)
//   player mouse sensitivity
# define PS_MOVE	0.1f
# define PS_ROTATE	0.0490873852123f
# define PS_MOUSE	1.0f

// Shading settings
// fog start
# define FOG_MIN	3.5f
// max view distance
# define FOG_MAX	10.0f

// Minimap settings
// postion
# define MM_POS_Y	10
# define MM_POS_X	10
// size
# define MM_SIZE_TILE	10
# define MM_SIZE_PLAYER	4

// Structure

// Mlx pointer for the window
enum e_mlx {
	INIT,
	WINDOW
};

// Mini map images
enum e_mm {
	MAP,
	PLAYER
};

enum e_tx {
	NO,
	SO,
	EA,
	WE,
	FL,
	CE,
	D,
	T
};

enum e_axis {
	X,
	Y,
};

// data struct to draw into an image
typedef struct s_img_data {
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img_data;

// Store all the textures informations:
// - the path to the texture
// - the pointer to the image
typedef struct s_texture {
	char		*path;
	t_img_data	img;
}	t_texture;

typedef struct s_inputs {
	bool	forward;
	bool	back;
	bool	m_left;
	bool	m_right;
	bool	r_left;
	bool	r_right;
}	t_inputs;

typedef struct s_player {
	float	pos[2];
	float	angle;
	float	delta[2];
}	t_player;

// distance between the player and the wall
// wall: NEWS
typedef struct s_ray {
	float			angle;
	float			delta[2];
	float			hit[2];
	float			distance;
	unsigned char	wall;
	int				hitdir;
}	t_ray;

// mlx: pointer on informations of the window
typedef struct s_info {
	void		*mlx[2];
	char		**map;
	t_img_data	mm_img[2];
	int			mapsize[2];
	t_player	player;
	t_inputs	inputs;
	t_texture	texture[8];
	bool		active_map;
	t_ray		ray[W_WIDTH];
	t_img_data	screen;
}	t_info;

// check_map.c
int		check_extension(char *mapname);
int		check_map_data(t_info *info);

// close.c
void	free_array(char **array);
int		error_msg(char *msg);
void	close_game(t_info *info, int exit_code);

// doors.c
int		check_doors(t_info *info, int y);

// init.c
int		init_game(t_info *info, char *mapname);

// frame.c
void	print_frame(t_info *info);

// mini_map.c
void	create_minimap(t_info *info);
void	print_minimap(t_info *info);

// parsing.c
int		load_map(t_info *info, char *mapname);

// player.c
void	player_move(t_info *info, float distance, int side);
void	player_rotate(t_info *info, float rotation);
void	player_action(t_info *info);

// ray.c
void	ray(t_info *info, t_ray *ray);

// rendering.c
void	render_screen(t_info *info);

// textures.c
int		load_textures(t_info *info);

// update.c
int		update_game(t_info *info);

// utils_math.c
void	angle_delta(float angle, float delta[2]);
float	angle_sum(float angle_a, float angle_b);
float	sqrt_points(float o[2], float d[2]);

// utils_mlx.c
void	my_destroy_image(void *mlx, void *img);
void	my_mouse_move(void *mlx, void *win, int x, int y);
void	my_mouse_get_pos(void *mlx, void *win, int *x, int *y);

// utils_parsing.c
char	*skip_whitespaces(char *str);
int		convert_rgb(char *rgb);

// utils_rays.c
float	horizontal_up(t_info *info, float hit[2], float delta[2]);
float	horizontal_down(t_info *info, float hit[2], float delta[2]);
float	vertical_right(t_info *info, float hit[2], float delta[2]);
float	vertical_left(t_info *info, float hit[2], float delta[2]);

// utils_render.c
void	add_shade(char *dst, float distance);
float	calc_x_scaling(t_ray *ray);

// window.c
int		start_window(t_info *info);

#endif /* CUB3D_H */
