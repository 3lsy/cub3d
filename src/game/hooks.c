/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 00:42:13 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/10 21:44:40 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_game(void *p _X_UNUSED)
{
	exit(EXIT_SUCCESS);
}

int	event_render(void *p)
{
	paint_mmap(p);
	return (0);
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
	if (keycode == ESC)
		exit(EXIT_SUCCESS);
	return (0);
}
