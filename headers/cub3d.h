/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:51:07 by gudias            #+#    #+#             */
/*   Updated: 2022/08/20 09:39:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// HEADERS

# include	<stdio.h>
# include	"keys.h"
# include "../libs/libft/includes/libft.h"

# ifdef __APPLE__
#  include	"../libs/mlx-apple/mlx.h"

# elif __linux__
#  include	"../libs/mlx-linux/mlx.h"
#  include	"../libs/mlx-linux/mlx_int.h"

# endif

#endif /* CUB3D_H */
