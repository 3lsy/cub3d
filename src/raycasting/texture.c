/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 23:57:50 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/20 23:58:22 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
