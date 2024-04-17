/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:12:47 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/17 11:37:21 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	TODO: Optimize this function. To not redraw the entire minimap.
**		- Only redraw the player and a few pixels around it. 
*/
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
	raycasting(world);
	paint_mmap(world);
}

/*
** First, the distance of the arrow must be the size of p.diameter.
** d[2]: Translated unitary vector to the center of the player.
**       resize the vector to the size of the arrow (p.diameter).
** m:    Slope of the arrow between the center of the player and the arrow.
** Slope: To verify if the point x,y is in the slope of the arrow, 
**        we use the equation of the line.
**        y - y1 = m(x - x1)
**		(y - p.my) - m(x - p.mx) < ARROW_W
**		(y - p.my) - m(x - p.mx) > -ARROW_W
**		(x - p.mx) - (y - p.my) / m < ARROW_W
**		(x - p.mx) - (y - p.my) / m > -ARROW_W
** mx: Center of the player in x in the minimap.
** my: Center of the player in y in the minimap.
*/
/// @brief Direction of the player. Arrow.
int	is_arrow(t_player p, int x, int y)
{
	double	d[2];
	double	m;

	if (pow(ARROW_LEN, 2) > pow(p.mx - x, 2) + pow(p.my - y, 2))
	{
		d[0] = cos(p.angle) * ARROW_LEN + p.mx;
		d[1] = -sin(p.angle) * ARROW_LEN + p.my;
		if (pow(ARROW_LEN - p.diameter / 2, 2)
			< pow(d[0] - x, 2) + pow(d[1] - y, 2))
			return (0);
		if (d[0] == p.mx && p.mx - ARROW_W < x && x < p.mx + ARROW_W)
			return (1);
		m = (d[1] - p.my) / (d[0] - p.mx);
		if (((y - p.my) - m * (x - p.mx) < ARROW_W
				&& (y - p.my) - m * (x - p.mx) > -ARROW_W)
			|| ((x - p.mx) - (y - p.my) / m < ARROW_W
				&& (x - p.mx) - (y - p.my) / m > -ARROW_W))
			return (1);
	}
	return (0);
}

