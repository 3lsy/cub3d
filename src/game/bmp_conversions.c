/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_conversions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 00:15:43 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/21 00:22:20 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_bmp_textures(t_graphics *graphics)
{
	graphics->texture_n_bmp = bmp_square(graphics->texture_n->width,
			graphics->texture_n->height, 0x000000);
	graphics->texture_s_bmp = bmp_square(graphics->texture_s->width,
			graphics->texture_s->height, 0x000000);
	graphics->texture_w_bmp = bmp_square(graphics->texture_w->width,
			graphics->texture_w->height, 0x000000);
	graphics->texture_e_bmp = bmp_square(graphics->texture_e->width,
			graphics->texture_e->height, 0x000000);
	img_to_bmp(graphics->texture_n, graphics->texture_n_bmp);
	img_to_bmp(graphics->texture_s, graphics->texture_s_bmp);
	img_to_bmp(graphics->texture_w, graphics->texture_w_bmp);
	img_to_bmp(graphics->texture_e, graphics->texture_e_bmp);
}

void	bmp_to_img(void *mlx, t_img *i, t_pair wh, int **bmp)
{
	int				x;
	int				y;
	int				color;
	int				fixed_color;
	unsigned char	*ptr;

	y = 0;
	while (y < wh.y)
	{
		ptr = (unsigned char *)i->data + y * i->size_line;
		x = 0;
		while (x < wh.x)
		{
			color = bmp[y][x];
			fixed_color = mlx_get_color_value(mlx, color);
			set_color_ptr(ptr, i, (unsigned char *)&fixed_color, x);
			x++;
		}
		y++;
	}
}

void	img_to_bmp(t_img *img, int **bmp)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			bmp[y][x] = get_pixel(img, x, y);
			x++;
		}
		y++;
	}
}
