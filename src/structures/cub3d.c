/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:31:11 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/10 12:12:25 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub3d	*cub(int action)
{
	static t_cub3d	x = {
		.fd = -1, .map_w = -1, .map_h = -1, .map = NULL, .llmap = NULL,
		.player = {
		.x = -1, .y = -1, .mx = -1, .my = -1, .dir_x = -1, .dir_y = -1,
		.move_speed = 1, .rot_speed = 0.1,
	},
		.graphics = {
		.mlx = NULL, .win = NULL, .texture_n = NULL, .texture_s = NULL,
		.texture_w = NULL, .texture_e = NULL, .mmap = NULL,
		.local_endian = -1, .ceiling_color = -1, .floor_color = -1,
	}
	};

	if (action == DESTRUCTOR)
		ft_destructor(&x);
	if (action == INIT)
		return (&x);
	return (NULL);
}
