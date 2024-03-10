/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:42:57 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/10 12:30:33 by echavez-         ###   ########.fr       */
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

/*
** x_event: path: /usr/include/X11/X.h
** x_mask : path: /usr/include/X11/X.h
** DestroyNotify: The window has been destroyed. (closed)
** ConfigureNotify: The window has been resized.
** UnmapNotify: The window has been unmapped. (minimized)
**
** The StructureNotifyMask in Xlib indicates that events related to 
** the structure of the window (such as creation, destruction, resizing, etc.)
** should be reported to the client.
*/
/// @brief init_hooks: Initialize hooks for the game.
static void	init_hooks(t_cub3d *world)
{
	mlx_hook(world->graphics.win,
		DestroyNotify, StructureNotifyMask, exit_game, world);
	mlx_hook(world->graphics.win, ConfigureNotify, StructureNotifyMask,
		empty_hook, world);
	mlx_hook(world->graphics.win, UnmapNotify, StructureNotifyMask,
		empty_hook, world);
	mlx_key_hook(world->graphics.win, key_press, world);
}

static void	init_graphics(t_cub3d *world)
{
	world->graphics.local_endian = local_endian();
	world->graphics.mlx = mlx_init();
	if (!world->graphics.mlx)
		exit_error(EMLX);
	init_window(world);
	init_hooks(world);

	new_mmap(&world->graphics, world);
	mlx_put_image_to_window(world->graphics.mlx, world->graphics.win,
		world->graphics.mmap, 0, 0);
}

void	game(t_cub3d *world)
{
	init_graphics(world);
	ft_printf("Game started\n");
	mlx_loop(world->graphics.mlx);
}
