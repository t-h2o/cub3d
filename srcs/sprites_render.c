/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 20:07:27 by gudias            #+#    #+#             */
/*   Updated: 2022/10/31 13:43:40 by gudias           ###   ########.fr       */
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
	if (tx_color != 0xFF000000)
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

void	render_sprites(t_info *info)
{	
	t_spriteview	*sprite;

	sprite = info->spriteview;
	sprite = info->spriteview;
	while (sprite)
	{
		draw_sprite(info, sprite);
		sprite = sprite->next;
	}
}
