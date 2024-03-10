/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:49:06 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/10 19:41:44 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	turn_left(t_cub3d *world)
{
	world->player.angle += world->player.turn_speed;
	world->player.angle = fmod(world->player.angle, 2 * M_PI);
	render(world);
}

void	turn_right(t_cub3d *world)
{
	world->player.angle += (2 * M_PI) - world->player.turn_speed;
	world->player.angle = fmod(world->player.angle, 2 * M_PI);
	render(world);
}