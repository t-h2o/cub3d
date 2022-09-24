/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:27:25 by gudias            #+#    #+#             */
/*   Updated: 2022/09/22 12:32:50 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img_data	*get_wall_tx(t_info *info, char wall)
{
	if (wall == NO)
		return (&(info->texture[NO].img));
	else if (wall == SO)
		return (&(info->texture[SO].img));
	else if (wall == WE)
		return (&(info->texture[WE].img));
	else if (wall == EA)
		return (&(info->texture[EA].img));
	return (NULL);
}
