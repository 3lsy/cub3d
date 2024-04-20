/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:17:09 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/21 00:23:03 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "libraries.h"

void	game(t_cub3d *world);

/*
** Img
*/

int		local_endian(void);
t_img	*new_img(void *mlx, int w, int h, int **bmp);
void	bmp_to_img(void *mlx, t_img *i, t_pair wh, int **bmp);
int		**bmp_square(int w, int h, int color);
void	render(t_cub3d *world);
void	paint_mmap(t_cub3d *world);
int		is_player(t_player p, int x, int y);
void	update_mmap(int ***bmp, t_pair m, t_player player, t_cub3d *world);
int		is_arrow(t_player p, int x, int y);
void	img_to_bmp(t_img *img, int **bmp);

/*
** Hooks
*/

int		exit_game(void *param);
int		event_render(void *p);
int		key_press(int keycode, void *p);

/*
** Movement
*/
void	move_up(t_cub3d *world);
void	move_down(t_cub3d *world);
void	move_left(t_cub3d *world);
void	move_right(t_cub3d *world);
void	turn_left(t_cub3d *world);
void	turn_right(t_cub3d *world);

/*
** BMP Conversions
*/
void	init_bmp_textures(t_graphics *graphics);
void	set_color_ptr(unsigned char *line, t_img *i,
			unsigned char	*ucolor, int x);
int		get_pixel(t_img *img, int x, int y);

#endif