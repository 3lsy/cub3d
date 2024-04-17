/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:46:39 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/17 18:53:36 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	new_bmp_3d(t_graphics *graphics, t_cub3d *word)
{
	graphics->bmp_3d = bmp_square(W_WIDTH, W_HEIGHT, 0x000000);
	(void)word;
}

void	new_strip(t_graphics *graphics, int x, int y, double len)
{
	int	i;

	while (y < W_HEIGHT && y < len)
	{
		i = x;
		while (i < W_WIDTH && i < x + STRIP_W)
		{
			if (i < W_WIDTH)
				graphics->bmp_3d[y][i] = 0x00FF00;
			i++;
		}
		y++;
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
	if (y_pos < 0)
		y_pos = 0;
	if (x < 0)
		x = 0;
	new_strip(graphics, W_WIDTH - x, y_pos, len + y_pos);
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
