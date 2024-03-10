/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 00:42:13 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/10 12:10:44 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_game(void *p _X_UNUSED)
{
	exit(EXIT_SUCCESS);
}

int	empty_hook(void *p _X_UNUSED)
{
	return (0);
}

int	key_press(int keycode, void *p _X_UNUSED)
{
	if (keycode == W)
		ft_printf("Move forward\n");
	else if (keycode == A)
		ft_printf("Move left\n");
	else if (keycode == S)
		ft_printf("Move back\n");
	else if (keycode == D)
		ft_printf("Move right\n");
	else if (keycode == L_ARROW)
		ft_printf("Turn left\n");
	else if (keycode == R_ARROW)
		ft_printf("Turn right\n");
	else if (keycode == ESC)
		exit(EXIT_SUCCESS);
	return (0);
}
