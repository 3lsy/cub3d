/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:12:47 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/11 23:51:47 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_mmap(int ***bmp, t_pair m, t_player player, t_cub3d *world)
{
	int	w;

	w = m.x;
	while (m.y-- > 0)
	{
		m.x = w;
		while (m.x-- > 0)
		{
			if (world->map[m.y / MMAP_SCALE][m.x / MMAP_SCALE].type == '1')
				(*bmp)[m.y][m.x] = MMAP_WALL;
			if (is_player(player, m.x, m.y))
				(*bmp)[m.y][m.x] = PLAYER_COLOR;
			else if (world->map[m.y / MMAP_SCALE][m.x / MMAP_SCALE].type == '0')
				(*bmp)[m.y][m.x] = MMAP_FLOOR;
			if (is_arrow(player, m.x, m.y))
				(*bmp)[m.y][m.x] = ARROW_COLOR;
		}
	}
}

void	paint_mmap(t_cub3d *world)
{
	if (!world->graphics.mmap)
		world->graphics.mmap = new_img(world->graphics.mlx,
				world->graphics.mmap_w, world->graphics.mmap_h,
				world->graphics.bmp);
	else
		bmp_to_img(world->graphics.mlx, world->graphics.mmap, (t_pair){
			world->graphics.mmap_w, world->graphics.mmap_h},
			world->graphics.bmp);
	mlx_put_image_to_window(world->graphics.mlx, world->graphics.win,
		world->graphics.mmap, 0, 0);
}

void	render(t_cub3d *world)
{
	update_mmap(&world->graphics.bmp, (t_pair){world->graphics.mmap_w,
		world->graphics.mmap_h}, world->player, world);
	paint_mmap(world);
}
