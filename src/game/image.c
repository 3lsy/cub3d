/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:36:11 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/21 00:17:23 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	local_endian(void)
{
	int	a;

	a = 0x11223344;
	return (((unsigned char *)&a)[0] == 0x11);
}

void	set_color_ptr(unsigned char *line, t_img *i,
	unsigned char	*ucolor, int x)
{
	int				byte;
	int				dec;
	int				opp;

	dec = i->bpp / 8;
	opp = dec;
	byte = x * i->bpp / 8;
	while (dec--)
	{
		if (i->image->byte_order == local_endian())
		{
			if (i->image->byte_order)
				*(line + byte + dec) = ((ucolor))[4 - opp + dec];
			else
				*(line + byte + dec) = ((ucolor))[dec];
		}
		else
		{
			if (i->image->byte_order)
				*(line + byte + dec) = ((ucolor))[opp - 1 - dec];
			else
				*(line + byte + dec) = ((ucolor))[3 - dec];
		}
	}
}

int	get_pixel(t_img *img, int x, int y)
{
	int		color;
	char	*dst;

	dst = img->data + (y * img->size_line + x * (img->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

t_img	*new_img(void *mlx, int w, int h, int **bmp)
{
	t_img	*new;

	new = mlx_new_image(mlx, w, h);
	if (!new)
		exit_error(EIMG);
	bmp_to_img(mlx, new, (t_pair){w, h}, bmp);
	return (new);
}

int	**bmp_square(int w, int h, int color)
{
	int	**bmp;
	int	x;
	int	y;

	bmp = malloc(sizeof(int *) * h);
	if (!bmp)
		exit_error(strerror(errno));
	y = 0;
	while (y < h)
	{
		bmp[y] = malloc(sizeof(int) * w);
		if (!bmp[y])
			exit_error(strerror(errno));
		x = 0;
		while (x < w)
		{
			bmp[y][x] = color;
			x++;
		}
		y++;
	}
	return (bmp);
}
