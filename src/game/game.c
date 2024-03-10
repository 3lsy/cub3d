/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:42:57 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/10 01:12:30 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_window(t_cub3d *world)
{
	world->graphics.win = mlx_new_window(world->graphics.mlx,
			W_WIDTH, W_HEIGHT, "cub3D");
	if (!world->graphics.win)
		exit_error(EWIN);

}

/// @var x_event: path: /usr/include/X11/X.h
/// @var x_mask : path: /usr/include/X11/X.h
static void	init_hooks(t_cub3d *world)
{
	mlx_hook(world->graphics.win,
		DestroyNotify, StructureNotifyMask, exit_game, world);
}

static void	init_graphics(t_cub3d *world)
{
	int	**bmp;

	world->graphics.local_endian = local_endian();
	world->graphics.mlx = mlx_init();
	if (!world->graphics.mlx)
		exit_error(EMLX);
	init_window(world);
	init_hooks(world);
	bmp = bmp_square(MMAP_W, MMAP_H, 0x222222);
	world->graphics.mmap_floor = new_img(world->graphics.mlx,
			MMAP_W, MMAP_H, bmp);
	free_bmp(bmp, MMAP_H);
	bmp = bmp_square(MMAP_W, MMAP_H, 0xFFFFFF);
	world->graphics.mmap_wall = new_img(world->graphics.mlx,
			MMAP_W, MMAP_H, bmp);
	free_bmp(bmp, MMAP_H);
}

void	game(t_cub3d *world)
{
	init_graphics(world);
	ft_printf("Game started\n");
	mlx_loop(world->graphics.mlx);
}
