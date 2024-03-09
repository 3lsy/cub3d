/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libraries.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:38:48 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/09 12:28:30 by echavez-         ###   ########.fr       */
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
** Keys
*/

# define W 119
# define A 97
# define S 114
# define D 115

# define L_ARROW 65361
# define R_ARROW 65363

# define ESC 65307
# define E_CLOSE 131072
# define E_MAXIM 131072
# define E_MINIM 131073

/*
** Map
** 1 := wall
** 0 := empty space
*/

typedef struct s_map
{
	char		type;
	int			x;
	int			y;
	t_bool		visited;
}	t_map;

/*
**	Graphics
**  win := windows
*/

typedef struct s_graphics
{
	void	*mlx;
	void	*win;
	t_img	*texture_n;
	t_img	*texture_s;
	t_img	*texture_w;
	t_img	*texture_e;
	int		ceiling_color;
	int		floor_color;
	int		local_endian;
}	t_graphics;

/*
** Player
*/

typedef struct player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	move_speed;
	double	rot_speed;
}	t_player;

/*
principal structure
*/

typedef struct s_cub3d
{
	int			map_width;
	int			map_height;
	t_map		**map;
	t_graphics	graphics;
}	t_cub3d;

#endif