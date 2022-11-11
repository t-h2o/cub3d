/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudias <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 11:58:14 by gudias            #+#    #+#             */
/*   Updated: 2022/11/08 20:12:26 by gudias           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

// minimap textures
# define MM_PLAYER	"assets/textures/minimap/player.xpm"
# define MM_EMPTY	0x70303030
# define MM_GROUND	0x00C1C1C1
# define MM_WALL	0x00000000
# define MM_DOOR	0x007C503F
# define MM_TORCH	0x00222222
# define MM_BARREL	0x00B8B8B8
# define MM_ENEMY	0x00660000

// default game textures
# define TX_NORTH	"assets/textures/dark_brick.xpm"
# define TX_SOUTH	"assets/textures/jungle.xpm"
# define TX_EAST	"assets/textures/jungle_brick.xpm"
# define TX_WEST	"assets/textures/handpainted_brick.xpm"
# define TX_FLOOR	"assets/textures/dirt1.xpm"
# define TX_CEIL	"assets/textures/sky_doubled.xpm"

// doors
# define TX_DOOR_NB	9

# define TX_DOOR	"assets/textures/doorend1.xpm"
# define TX_DOOR2	"assets/textures/doorend2.xpm"
# define TX_DOOR3	"assets/textures/doorend3.xpm"
# define TX_DOOR4	"assets/textures/doorend4.xpm"
# define TX_DOOR5	"assets/textures/doorend5.xpm"
# define TX_DOOR6	"assets/textures/doorend6.xpm"
# define TX_DOOR7	"assets/textures/doorend7.xpm"
# define TX_DOOR8	"assets/textures/doorend8.xpm"
# define TX_DOOR9	"assets/textures/doorend9.xpm"

// sprites
# define TX_TORCH_NB	3

# define TX_TORCH1	"assets/textures/sprites/torch_01.xpm"
# define TX_TORCH2	"assets/textures/sprites/torch_02.xpm"
# define TX_TORCH3	"assets/textures/sprites/torch_03.xpm"

# define TX_BARREL	"assets/textures/sprites/barrel.xpm"
# define TX_ENEMY	"assets/textures/sprites/golem.xpm"

// POV (hands, weapons, ...)
# define TX_PISTOL_NB	6

# define TX_PISTOL1	"assets/textures/pistol1/01F.xpm"
# define TX_PISTOL2	"assets/textures/pistol1/02F.xpm"
# define TX_PISTOL3	"assets/textures/pistol1/03F.xpm"
# define TX_PISTOL4	"assets/textures/pistol1/04F.xpm"
# define TX_PISTOL5	"assets/textures/pistol1/05F.xpm"
# define TX_PISTOL6	"assets/textures/pistol1/06F.xpm"

#endif /* TEXTURES_H */
