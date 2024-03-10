/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:32:16 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/10 20:22:51 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// printf("player angle: %f x: %f y: %f\n", world->player.angle,
//  world->player.mx, world->player.my);
void	move_up(t_cub3d *world)
{
	world->player.mx += cos(world->player.angle) * world->player.move_speed;
	world->player.my -= sin(world->player.angle)
		* world->player.move_speed;
	render(world);
}

void	move_down(t_cub3d *world)
{
	world->player.mx += cos(world->player.angle + M_PI)
		* world->player.move_speed;
	world->player.my -= sin(world->player.angle + M_PI)
		* world->player.move_speed;
	render(world);
}

void	move_left(t_cub3d *world)
{
	world->player.mx += cos(world->player.angle + M_PI / 2)
		* world->player.move_speed;
	world->player.my -= sin(world->player.angle + M_PI / 2)
		* world->player.move_speed;
	render(world);
}

void	move_right(t_cub3d *world)
{
	world->player.mx += cos(world->player.angle - M_PI / 2)
		* world->player.move_speed;
	world->player.my -= sin(world->player.angle - M_PI / 2)
		* world->player.move_speed;
	render(world);
}
