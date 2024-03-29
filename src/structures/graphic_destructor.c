/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_destructor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:44:03 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/10 14:19:18 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	graphic_destructor(t_graphics *graphics)
{
	if (graphics->texture_n)
		mlx_destroy_image(graphics->mlx, graphics->texture_n);
	if (graphics->texture_s)
		mlx_destroy_image(graphics->mlx, graphics->texture_s);
	if (graphics->texture_w)
		mlx_destroy_image(graphics->mlx, graphics->texture_w);
	if (graphics->texture_e)
		mlx_destroy_image(graphics->mlx, graphics->texture_e);
	if (graphics->mmap)
		mlx_destroy_image(graphics->mlx, graphics->mmap);
	if (graphics->win)
	{
		mlx_clear_window(graphics->mlx, graphics->win);
		mlx_destroy_window(graphics->mlx, graphics->win);
	}
	if (graphics->mlx)
	{
		mlx_destroy_display(graphics->mlx);
		free(graphics->mlx);
	}
	if (graphics->bmp)
		free_bmp(&graphics->bmp, graphics->mmap_h);
}
