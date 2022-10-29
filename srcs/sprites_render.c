/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:07:27 by gudias            #+#    #+#             */
/*   Updated: 2022/10/29 20:42:49 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_sprite_pixel(t_info *info, t_spriteview *sprite, int x, int y)
{
	char			*dst;
	unsigned int	tx_color;
	t_img_data		*tx;

	dst = info->screen.addr + (y * info->screen.line_len)
		+ (x * info->screen.bpp / 8);
	if (sprite->type == 'T')
		tx = &(info->texture[T1 + info->torch_frame].img);
	else
		tx = &(info->texture[ENEMY].img);
	tx_color = get_tx_pixel(tx,
			(float)(x - sprite->draw_start[X]) / sprite->width,
			(float)(y - sprite->draw_start[Y]) / sprite->height);
	if (tx_color != 0xFF000000 && tx_color != 0)
	{
		*(unsigned int *)dst = tx_color;
		add_shade(dst, sprite->distance / 1.5f);
	}
}

static void	draw_sprite(t_info *info, t_spriteview *sprite)
{
	int			line;
	int			col;

	if (sprite->distance > FOG_MAX)
		return ;
	col = sprite->draw_start[X] - 1;
	while (++col < sprite->draw_end[X] && col < W_WIDTH)
	{
		if (col < 0 || info->ray[col].distance < sprite->distance)
			continue ;
		line = sprite->draw_start[Y] - 1;
		while (++line < sprite->draw_end[Y] && line < W_HEIGHT)
		{
			if (line < 0)
				continue ;
			draw_sprite_pixel(info, sprite, col, line);
		}
	}
}

static void	calc_sprite_view(t_info *info, t_spriteview *sprite)
{
	int		screen_x;
	float	det;
	float	x_transform;

	det = 1.0f / ((-info->player.delta[Y] * tan(FOV / 2))
			* info->player.delta[Y] - info->player.delta[X]
			* (info->player.delta[X] * tan(FOV / 2)));
	x_transform = det * (info->player.delta[Y] * sprite->pos[X]
			- info->player.delta[X] * sprite->pos[Y]);
	sprite->distance = det * (-(info->player.delta[X] * tan(FOV / 2))
			* sprite->pos[X] + (-info->player.delta[Y] * tan(FOV / 2))
			* sprite->pos[Y]);
	screen_x = (int)((W_WIDTH / 2) * (1 + x_transform
				/ sprite->distance));
	sprite->height = W_HEIGHT / sprite->distance;
	sprite->draw_end[Y] = sprite->height / 2 + W_HEIGHT / 2;
	//sprite->height = sprite->height / 2;
	sprite->draw_start[Y] = sprite->draw_end[Y] - sprite->height;
	sprite->width = ((float)sprite->height
			/ info->texture[T1 + info->torch_frame].img.height)
		* info->texture[T1 + info->torch_frame].img.width;
	sprite->draw_start[X] = -sprite->width / 2 + screen_x;
	sprite->draw_end[X] = sprite->width / 2 + screen_x;
}

void	render_sprites(t_info *info)
{	
	t_spriteview	*sprite;

	sprite = info->spriteview;
	while (sprite)
	{
		sprite->pos[X] = sprite->pos[X] - info->player.pos[X];
		sprite->pos[Y] = sprite->pos[Y] - info->player.pos[Y];
		calc_sprite_view(info, sprite);
		sprite = sprite->next;
	}
	//sort_sprites(info);
	sprite = info->spriteview;
	while (sprite)
	{
		draw_sprite(info, sprite);
		sprite = sprite->next;
	}
}
