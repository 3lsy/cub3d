/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libraries.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:38:48 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/17 19:01:11 by echavez-         ###   ########.fr       */
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

# define TURN_SPEED 0.1
# define MOVE_SPEED 2

/*
** Raycasting
*/

# define FOV 60
# define ANGLE_UNIT 0.01
# define MAX_DEPTH 20
# define FOV_COLOR 0x00FF00

/*
** 3D Map
*/

# define STRIP_W 8
# define CUBE_H 20

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
	t_img	*texture_s;
	t_img	*texture_w;
	t_img	*texture_e;
	int		ceiling_color;
	int		floor_color;
	int		mmap_w;
	int		mmap_h;
	t_img	*mmap;
	t_img	*map_3d;
	int		**bmp;
	int		**bmp_3d;
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