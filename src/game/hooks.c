/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 00:42:13 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/18 21:16:57 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_game(void *p _X_UNUSED)
{
	exit(EXIT_SUCCESS);
}

int	event_render(void *p)
{
	t_cub3d	*world;

	world = (t_cub3d *)p;
	paint_3d(world);
	if (world->graphics.mmap_on)
		paint_mmap(world);
	return (0);
}

void	toggle_minimap(t_cub3d *world)
{
	world->graphics.mmap_on = !world->graphics.mmap_on;
	render(world);
}

int	key_press(int keycode, void *p)
{
	if (keycode == W)
		move_up(p);
	else if (keycode == A)
		move_left(p);
	else if (keycode == S)
		move_down(p);
	else if (keycode == D)
		move_right(p);
	else if (keycode == L_ARROW)
		turn_left(p);
	else if (keycode == R_ARROW)
		turn_right(p);
	else if (keycode == M)
		toggle_minimap(p);
	else if (keycode == ESC)
		exit(EXIT_SUCCESS);
	return (0);
}
