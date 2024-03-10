/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:17:09 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/10 10:14:14 by echavez-         ###   ########.fr       */
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
int		**bmp_square(int w, int h, int color);

/*
** Hooks
*/

int		exit_game(void *param);
int		empty_hook(void *p);
int		key_press(int keycode, void *p);

#endif