/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:54:21 by gudias            #+#    #+#             */
/*   Updated: 2022/10/26 04:19:56 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_sprite(t_info *info, float pos[2])
{
	t_spriteview	*new;
	t_spriteview	*ptr;

	ptr = info->spriteview;
	while (ptr)
	{
		if ((int)ptr->pos[X] == (int)pos[X]
			&& (int)ptr->pos[Y] == (int)pos[Y])
			return ;
		ptr = ptr->next;
	}
	new = malloc(sizeof (t_spriteview));
	if (!new)
		return ;
	new->pos[X] = (int)pos[X] + 0.5f;
	new->pos[Y] = (int)pos[Y] + 0.5f;
	new->next = info->spriteview;
	info->spriteview = new;
}

void	sort_sprites(t_info *info)
{
	t_spriteview	*ptr;
	//t_spriteview	*tmp;
	
	ptr = info->spriteview;
	while (ptr->next)
	{
		if (ptr->transform[Y] < ptr->next->transform[Y])
		{

		}
		ptr = ptr->next;
	}
}

void	free_sprite_list(t_spriteview *list)
{
	t_spriteview *tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}
