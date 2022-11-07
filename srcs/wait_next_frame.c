/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_next_frame.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:22:49 by user42            #+#    #+#             */
/*   Updated: 2022/11/07 20:50:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"cub3d.h"
#include	<sys/time.h>
#include	<time.h>

// Time for a frame [ms]
#define TIME_FRAME	20

// Return delta time between now and last [ms]
static int
	time_now(struct timeval *now, struct timeval *last)
{
	unsigned int	delta_time;

	gettimeofday(now, 0);
	delta_time = (unsigned int)(((now->tv_sec - last->tv_sec) * 1000) \
		+ ((now->tv_usec - last->tv_usec) / 1000));
	return ((int)delta_time);
}

// If it's the first frame, init time "last frame"
// Else, wait the time for a frame
void	wait_next_frame(t_info *info)
{
	if (info->time.last.tv_sec == 0)
	{
		gettimeofday(&(info->time.last), 0);
		return ;
	}
	while (time_now(&(info->time.now), &(info->time.last)) < TIME_FRAME)
	{
	}
	ft_memcpy(&(info->time.last), &(info->time.now), sizeof(struct timeval));
}
