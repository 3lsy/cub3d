/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libraries.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:38:48 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/10 13:37:34 by echavez-         ###   ########.fr       */
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

# define MMAP_H 30
# define MMAP_W 30
# define MMAP_FLOOR 0xDDDDDD
# define MMAP_WALL 0x222222

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
** Cube structure options
*/

# define DESTRUCTOR 0
# define INIT 1

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
	t_img	*mmap;
}	t_graphics;

/*
** Player
** x, y := player position
** mx, my := minimap position
*/

typedef struct s_player
{
	double	x;
	double	y;
	double	mx;
	double	my;
	double	dir_x;
	double	dir_y;
	double	move_speed;
	double	rot_speed;
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
	t_player	player;
	t_map		**map;
	t_doubly	*llmap;
	t_graphics	graphics;
}	t_cub3d;

#endif