/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:31:11 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/09 18:50:08 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub3d	*cub(int action)
{
	static t_cub3d	x = {
		.fd = -1,
		.map_w = -1,
		.map_h = -1,
		.map = NULL,
		.llmap = NULL,
		.graphics = {
		.mlx = NULL,
		.win = NULL,
		.local_endian = -1,
		.texture_n = NULL,
		.texture_s = NULL,
		.texture_w = NULL,
		.texture_e = NULL,
		.ceiling_color = -1,
		.floor_color = -1,
	}
	};

	if (action == DESTRUCTOR)
		ft_destructor(&x);
	return (&x);
}
