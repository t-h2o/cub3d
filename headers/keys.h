/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melogr@phy <tgrivel@student.42lausanne.ch  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:21:41 by melogr@phy        #+#    #+#             */
/*   Updated: 2022/09/24 19:29:10 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# ifdef __APPLE__

#  define KEY_A		0
#  define KEY_S		1
#  define KEY_D		2
#  define KEY_W		13
#  define KEY_Q		12
#  define KEY_E		14

#  define KEY_LEFT		123
#  define KEY_DOWN		125
#  define KEY_RIGHT		124
#  define KEY_UP		126

#  define KEY_ESC		53
#  define KEY_TAB		48

# elif __linux__

#  define KEY_A			97
#  define KEY_S			115
#  define KEY_D			100
#  define KEY_W			119
#  define KEY_Q			113
#  define KEY_E			101

#  define KEY_LEFT		65361
#  define KEY_DOWN		65364
#  define KEY_RIGHT		65363
#  define KEY_UP		65362

#  define KEY_ESC		65307
#  define KEY_TAB		65289

# endif

#endif /* KEYS_H */
