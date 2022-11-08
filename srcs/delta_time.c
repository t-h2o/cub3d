/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_next_frame.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:22:49 by user42            #+#    #+#             */
/*   Updated: 2022/11/08 15:16:48 by tgrivel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	<sys/time.h>
#include	<time.h>

// Return delta time between now and last [ms]
static unsigned int
	calcule_delta_time(struct timeval *now, struct timeval *last)
{
	unsigned int	delta_time;

	gettimeofday(now, 0);
	delta_time = (unsigned int)(((now->tv_sec - last->tv_sec) * 1000) \
		+ ((now->tv_usec - last->tv_usec) / 1000));
	return (delta_time);
}

// Fill the delta time
void	delta_time(t_info *info)
{
	if (info->time.last.tv_sec == 0)
	{
		gettimeofday(&(info->time.last), 0);
		return ;
	}
	info->time.delta_time = calcule_delta_time(&(info->time.now), &(info->time.last));
	ft_memcpy(&(info->time.last), &(info->time.now), sizeof(struct timeval));
	return ;
}
