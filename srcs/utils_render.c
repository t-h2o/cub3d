/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:54:39 by gudias            #+#    #+#             */
/*   Updated: 2022/11/10 18:09:14 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	calc_x_scaling(t_ray *ray, bool is_door)
{
	if (!is_door)
	{
		if (ray->hitdir)
			return (ray->hit[X] - (int)ray->hit[X]);
		else
			return (ray->hit[Y] - (int)ray->hit[Y]);
	}
	else
	{
		if (ray->doordir)
			return (ray->door_hit[X] - (int)ray->door_hit[X]);
		else
			return (ray->door_hit[Y] - (int)ray->door_hit[Y]);
	}
}

void	add_shade(char *dst, float distance)
{
	float		shading;

	if (distance <= FOG_MIN)
		return ;
	shading = 1 / (distance - FOG_MIN + 1);
	dst[0] = (unsigned char)dst[0] * shading;
	dst[1] = (unsigned char)dst[1] * shading;
	dst[2] = (unsigned char)dst[2] * shading;
}

void	draw_crosshair(t_info *info)
{
	char	*h_dst;
	char	*v_dst;
	int		i;

	h_dst = info->screen.addr + ((W_HEIGHT / 2) * info->screen.line_len)
		+ (((W_WIDTH / 2) - CROSSHAIR_SIZE - (CROSSHAIR_GAP / 2))
			* info->screen.bpp / 8);
	v_dst = info->screen.addr + ((W_WIDTH / 2) * info->screen.bpp / 8)
		+ (((W_HEIGHT / 2) - CROSSHAIR_SIZE - (CROSSHAIR_GAP / 2))
			* info->screen.line_len);
	i = -1;
	while (++i < CROSSHAIR_SIZE)
	{
		*(unsigned int *)h_dst = CROSSHAIR_COLOR;
		*(unsigned int *)(h_dst + (CROSSHAIR_SIZE + CROSSHAIR_GAP)
				* (info->screen.bpp / 8)) = CROSSHAIR_COLOR;
		*(unsigned int *)v_dst = CROSSHAIR_COLOR;
		*(unsigned int *)(v_dst + (CROSSHAIR_SIZE + CROSSHAIR_GAP)
				* info->screen.line_len) = CROSSHAIR_COLOR;
		h_dst += info->screen.bpp / 8;
		v_dst += info->screen.line_len;
	}
}

void	copy_image(t_img_data *dst_img, t_img_data *src_img)
{
	char		*dst;
	int			x;
	int			y;

	dst = dst_img->addr;
	y = -1;
	while (++y < dst_img->height)
	{
		x = -1;
		while (++x < dst_img->width)
		{
			*(unsigned int *)dst = get_tx_pixel(src_img,
					(float)x / dst_img->width,
					(float)y / dst_img->height);
			dst += (dst_img->bpp / 8);
		}
	}
}

void	draw_pov(t_info *info)
{
	t_img_data	*tx;
	char		*dst;
	char		*src;
	int			x;
	int			y;

	tx = &(info->texture[PISTOL1 + info->player.attack_frame].img);
	src = tx->addr;
	y = -1;
	while (++y < tx->height)
	{
		dst = info->screen.addr
			+ ((W_HEIGHT - tx->height + y) * info->screen.line_len)
			+ ((W_WIDTH / 4) * (info->screen.bpp / 8));
		x = -1;
		while (++x < tx->width)
		{
			if (*(unsigned int *)src != 0xFF000000)
				*(unsigned int *)dst = *(unsigned int *)src;
			dst += info->screen.bpp / 8;
			src += tx->bpp / 8;
		}
	}
}
