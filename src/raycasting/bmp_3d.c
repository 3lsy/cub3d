/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:46:39 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/20 23:58:24 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	new_bmp_3d(t_graphics *graphics, t_cub3d *world)
{
	graphics->bmp_3d = bmp_square(W_WIDTH, W_HEIGHT, 0x000000);
	(void)world;
}

void	new_strip(t_graphics *graphics, t_player *p, t_pair m, double len)
{
	int	i;
	int	j;

	j = m.y;
	if (j < 0)
		j = 0;
	while (j < W_HEIGHT && j < len)
	{
		i = m.x;
		if (i < 0)
			i = 0;
		while (i < W_WIDTH && i < m.x + graphics->strip_w)
		{
			if (i < W_WIDTH)
				graphics->bmp_3d[j][i] = texture_pixel(graphics, p,
						j - m.y, len - m.y);
			i++;
		}
		j++;
	}
}

/*
** Use this function each cast of a ray to paint the strip.
*/
void	paint_strip(t_graphics *graphics, t_player *p, int x)
{
	double	len;
	int		y_pos;

	len = (W_HEIGHT / p->ray.depth) * CUBE_H;
	y_pos = (W_HEIGHT - len) / 2;
	if (x < 0)
		x = 0;
	new_strip(graphics, p, (t_pair){W_WIDTH - x, y_pos}, len + y_pos);
}

void	paint_3d(t_cub3d *world)
{
	if (!world->graphics.map_3d)
		world->graphics.map_3d = new_img(world->graphics.mlx,
				W_WIDTH, W_HEIGHT, world->graphics.bmp_3d);
	else
		bmp_to_img(world->graphics.mlx, world->graphics.map_3d,
			(t_pair){W_WIDTH, W_HEIGHT}, world->graphics.bmp_3d);
	mlx_put_image_to_window(world->graphics.mlx, world->graphics.win,
		world->graphics.map_3d, 0, 0);
}
