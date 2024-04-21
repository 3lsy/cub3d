/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libraries.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:38:48 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/21 10:39:33 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARIES_H
# define LIBRARIES_H

# include "libft.h"
# include <stdio.h>    // printf
# include <stdlib.h>   // malloc, free, exit
# include <fcntl.h>    // open file
# include <unistd.h>   // close, read, write
# include <errno.h>    // perror, strerror
# include <math.h>     // math functions (-lm required during compilation)
# include <mlx.h>      // MinilibX
# include <mlx_int.h>  // MinilibX

/*
** Window size
*/
# define W_HEIGHT 720
# define W_WIDTH 1280

/*
** Minimap sprite size
*/

# define MMAP_SCALE 15
# define MMAP_FLOOR 0xDDDDDD
# define MMAP_WALL 0x222222
// Scale percentage
# define PLAYER_SIZE 0.5
# define PLAYER_COLOR 0xff8da1
// Arrow thickness in pixels
# define ARROW_W 2
# define ARROW_LEN 7
# define ARROW_COLOR 0x000000

# define TURN_SPEED 0.009
# define MOVE_SPEED 2

/*
** Raycasting
** 60 = M_PI / 3
** (x * M_PI) / (M_PI / 3) = x * 3
** Fixed FOV
** strip_w depends on FOV
*/

# define FOV 60
# define ANGLE_UNIT 0.0005
# define MAX_DEPTH 20
# define FOV_COLOR 0x00FF00
# define X_AXIS 0
# define Y_AXIS 1

/*
** 3D Map
*/

# define CUBE_H 30

/*
** Error messages
*/

# define USAGE "cub3d: Usage: ./cub3d <map.cub>\n"
# define EPERIMETER "cub3d: Unclosed map perimeter\n"
# define EFILE "cub3d: Couldn't open file\n"
# define EELMAP "cub3d: Empty line in map\n"
# define EMLX "cub3d: Minilibx init error\n"
# define EWIN "cub3d: Minilibx window error\n"
# define EIMG "cub3d: Minilibx image error\n"
# define ECUB "cub3d: Invalid extention for .cub file\n"
# define EINFO "cub3d: Too much information for one element\n"
# define EPATH "cub3d: Invalid path for xpm file\n"
# define EDUP "cub3d: Duplicate identifier detected\n"
# define EEXP "cub3d: Invalid texture file extention\n"
# define EMRGB "cub3d: Missing RGB information\n"
# define ECOLOR "cub3d: Invalid RGB set\n"
# define EUNKNOWN "cub3d: Unkown element detected\n"
# define EIEMAP "cub3d: Invalid element in map line\n"
# define EMULP "cub3d: Multiple player detected\n"
# define EWALLO "cub3d: Map must be surrunded by wall(outline)\n"
# define EWALLI "cub3d: Map must be surrunded by wall(inner)\n"
# define EMNLE "cub3d: Map is not the last element\n"
# define EMMAP "cub3d: Map element missing\n"
# define EMTEXT "cub3d: Texture element missing\n"
# define EMCOLOR "cub3d: Color element missing\n"
# define EMPLAYER "cub3d: Player missing\n"
# define EXPM "cub3d: Invalid xpm file\n"

/*
** Keys
*/

# define W 119
# define A 97
# define S 114
# define D 115

# define L_ARROW 65361
# define R_ARROW 65363

# define ESC 65307

// Toggle minimap
# define M 109

/*
** Structure options
*/

# define DESTRUCTOR 0
# define INIT 1
# define FLOOR 1
# define PLAYER 2

/*
**	Graphics
**  win := windows
**  mlx := minilibx
**  local_endian := endianess
**  mmap := minimap
*/

typedef struct s_graphics
{
	void	*mlx;
	void	*win;
	int		local_endian;
	t_img	*texture_n;
	int		**texture_n_bmp;
	t_img	*texture_s;
	int		**texture_s_bmp;
	t_img	*texture_w;
	int		**texture_w_bmp;
	t_img	*texture_e;
	int		**texture_e_bmp;
	int		ceiling_color;
	int		floor_color;
	int		mmap_w;
	int		mmap_h;
	t_img	*mmap;
	t_img	*map_3d;
	int		**bmp;
	int		**bmp_3d;
	int		mmap_on;
	double	strip_w;
}	t_graphics;

/*
** Raycasting
** xy := x and y position (x, y)
** dir := Ray direction on (x, y)
** russ := Ray unitary step size (x, y)
** len_1d_axis := lenght 1 dimension on axis (x, y)
*/
typedef struct s_raycasting
{
	double	xy[2];
	double	dir[2];
	double	russ[2];
	double	len_1d_axis[2];
	double	step[2];
	double	vray[2];
	double	depth;
	int		hit_axis;
}	t_raycasting;

/*
** Player
** x, y := player position
** mx, my := minimap position
*/

typedef struct s_player
{
	double			x;
	double			y;
	double			mx;
	double			my;
	double			angle;
	double			dir[2];
	double			move_speed;
	double			turn_speed;
	double			diameter;
	t_raycasting	ray;
}	t_player;

/// @brief Linked list map
typedef struct s_llmap
{
	char			*line;
	struct s_llmap	*next;
}	t_llmap;

typedef struct s_map
{
	char	type;
	int		x;
	int		y;
	int		visited;
}	t_map;

/*
principal structure
*/

typedef struct s_cub3d
{
	int			fd;
	int			map_w;
	int			map_h;
	t_map		**map;
	t_doubly	*llmap;
	t_player	player;
	t_graphics	graphics;
}	t_cub3d;

#endif