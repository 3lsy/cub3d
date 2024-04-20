/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:46:39 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/20 21:29:26 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	new_bmp_3d(t_graphics *graphics, t_cub3d *world)
{
	graphics->bmp_3d = bmp_square(W_WIDTH, W_HEIGHT, 0x000000);
	(void)world;
}

int	texture_color_x(t_graphics *graphics, t_player *p, int y, double len)
{
	int	**bmp;
	int	tw;
	int	th;

	if (p->ray.dir[0] < 0)
	{
		tw = graphics->texture_e->width;
		th = graphics->texture_e->height;
		bmp = graphics->texture_e_bmp;
	}
	else
	{
		tw = graphics->texture_w->width;
		th = graphics->texture_w->height;
		bmp = graphics->texture_w_bmp;
	}
	return (bmp[(int)(y * th / len)]
		[(int)(fmod(p->ray.vray[1], MMAP_SCALE) * tw / MMAP_SCALE)]);
}

int	texture_color_y(t_graphics *graphics, t_player *p, int y, double len)
{
	int	**bmp;
	int	tw;
	int	th;

	if (p->ray.dir[1] < 0)
	{
		tw = graphics->texture_s->width;
		th = graphics->texture_s->height;
		bmp = graphics->texture_s_bmp;
	}
	else
	{
		tw = graphics->texture_n->width;
		th = graphics->texture_n->height;
		bmp = graphics->texture_n_bmp;
	}
	return (bmp[(int)(y * th / len)]
		[(int)(fmod(p->ray.vray[0], MMAP_SCALE) * tw / MMAP_SCALE)]);
}

int	texture_pixel(t_graphics *graphics, t_player *p, int y, double len)
{
	if (p->ray.hit_axis == X_AXIS)
		return (texture_color_x(graphics, p, y, len));
	else if (p->ray.hit_axis == Y_AXIS)
		return (texture_color_y(graphics, p, y, len));
	return (0x000000);
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
