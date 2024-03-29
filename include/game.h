/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:17:09 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/13 10:19:00 by echavez-         ###   ########.fr       */
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

#endif