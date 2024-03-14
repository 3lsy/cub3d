/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 18:42:57 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/14 10:39:59 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		event_render, world);
	mlx_hook(world->graphics.win, UnmapNotify, StructureNotifyMask,
		event_render, world);
	// mlx_key_hook(world->graphics.win, key_press, world);
	mlx_hook(world->graphics.win,
		KeyPress, KeyPressMask, key_press, world);
}

static void	init_window(t_cub3d *world)
{
	world->graphics.win = mlx_new_window(world->graphics.mlx,
			W_WIDTH, W_HEIGHT, "cub3D");
	if (!world->graphics.win)
		exit_error(EWIN);
}

static void	init_graphics(t_cub3d *world)
{
	world->graphics.local_endian = local_endian();
	world->graphics.mlx = mlx_init();
	if (!world->graphics.mlx)
		exit_error(EMLX);
	init_window(world);
	new_bmp(&world->graphics, world);
}

void	game(t_cub3d *world)
{
	init_graphics(world);
	init_hooks(world);
	render(world);
	mlx_loop(world->graphics.mlx);
}
