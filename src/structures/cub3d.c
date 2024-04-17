/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:31:11 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/17 18:08:08 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub3d	*cub(int action)
{
	static t_cub3d	x = {
		.fd = -1, .map_w = -1, .map_h = -1, .map = NULL, .llmap = NULL,
		.player = {
		.x = -1, .y = -1, .mx = -1, .my = -1, .angle = 0,
		.move_speed = MOVE_SPEED, .turn_speed = TURN_SPEED * M_PI,
		.diameter = MMAP_SCALE * PLAYER_SIZE, .ray = {
		.xy = {-1, -1}, .dir = {-1, -1}, .russ = {-1, -1}, .step = {0, 0},
		.len_1d_axis = {-1, -1}, .vray = {0, 0}, .depth = -1
	}
	},
		.graphics = {
		.mlx = NULL, .win = NULL, .texture_n = NULL, .texture_s = NULL,
		.texture_w = NULL, .texture_e = NULL, .mmap = NULL, .bmp = NULL,
		.map_3d = NULL, .bmp_3d = NULL,
		.local_endian = -1, .ceiling_color = -1, .floor_color = -1,
		.mmap_w = -1, .mmap_h = -1, .mmap_on = 1,
	}
	};

	if (action == DESTRUCTOR)
		ft_destructor(&x);
	if (action == INIT)
		return (&x);
	return (NULL);
}
