/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:54:21 by gudias            #+#    #+#             */
/*   Updated: 2022/10/31 01:01:49 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (sprite->type == 'T')
		sprite->height = sprite->height / 2;
	sprite->draw_start[Y] = sprite->draw_end[Y] - sprite->height;
	sprite->width = ((float)sprite->height
			/ info->texture[T1 + info->torch_frame].img.height)
		* info->texture[T1 + info->torch_frame].img.width;
	sprite->draw_start[X] = -sprite->width / 2 + screen_x;
	sprite->draw_end[X] = sprite->width / 2 + screen_x;
}

static void	add_to_list(t_info *info, t_spriteview *new)
{
	t_spriteview	*ptr;

	ptr = info->spriteview;
	if (!ptr || new->distance >= ptr->distance)
	{
		new->next = ptr;
		info->spriteview = new;
		return ;
	}
	while (ptr)
	{
		if (ptr->next && new->distance > ptr->next->distance)
		{
			new->next = ptr->next;
			ptr->next = new;
			return ;
		}
		else if (!ptr->next)
		{
			new->next = NULL;
			ptr->next = new;
			return ;
		}
		ptr = ptr->next;
	}
}

void	add_sprite(t_info *info, float pos[2], char type)
{
	t_spriteview	*new;
	t_spriteview	*ptr;

	ptr = info->spriteview;
	while (ptr)
	{
		if (ptr->origin[X] == (int)pos[X]
			&& ptr->origin[Y] == (int)pos[Y])
			return ;
		ptr = ptr->next;
	}	
	new = malloc(sizeof (t_spriteview));
	if (!new)
		return ;
	new->origin[X] = pos[X];
	new->origin[Y] = pos[Y];
	new->pos[X] = (int)pos[X] + 0.5f - info->player.pos[X];
	new->pos[Y] = (int)pos[Y] + 0.5f - info->player.pos[Y];
	new->type = type;
	calc_sprite_view(info, new);
	add_to_list(info, new);
}

void	free_sprite_list(t_spriteview *list)
{
	t_spriteview	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}
