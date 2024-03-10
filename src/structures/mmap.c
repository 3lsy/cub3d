/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:17:17 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/10 13:36:48 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	paint_mmap(int ***bmp, int mw, int mh, t_map **map)
{
	int	w;

	w = mw;
	while (mh-- > 0)
	{
		mw = w;
		while (mw-- > 0)
		{
			if (map[mh / MMAP_H][mw / MMAP_W].type == '1')
				(*bmp)[mh][mw] = MMAP_WALL;
			if (map[mh / MMAP_H][mw / MMAP_W].type == '0')
				(*bmp)[mh][mw] = MMAP_FLOOR;
		}
	}
}

void	new_mmap(t_graphics *graphics, t_cub3d *world)
{
	int	**bmp;

	bmp = bmp_square(world->map_w * MMAP_W, world->map_h * MMAP_H, 0x000000);
	paint_mmap(&bmp, world->map_w * MMAP_W, world->map_h * MMAP_H, world->map);
	graphics->mmap = new_img(graphics->mlx, world->map_w * MMAP_W,
			world->map_h * MMAP_H, bmp);
	free_bmp(&bmp, world->map_h * MMAP_H);
}
