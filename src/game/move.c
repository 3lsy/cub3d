/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:32:16 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/18 01:24:55 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// printf("player angle: %f x: %f y: %f\n", world->player.angle,
//  world->player.mx, world->player.my);
void	move_up(t_cub3d *world)
{
	double	x;
	double	y;

	x = world->player.mx + cos(world->player.angle) * world->player.move_speed;
	y = world->player.my - sin(world->player.angle) * world->player.move_speed;
	if (world->graphics.bmp[(int)y][(int)x] == MMAP_WALL
		|| world->graphics.bmp[(int)y][(int)x] == 0x000000
		|| world->graphics.bmp[(int)y][(int)x] == FOV_COLOR
		|| world->map[(int)(y / MMAP_SCALE)][(int)(x / MMAP_SCALE)].type == '1'
		|| world->map[(int)(y / MMAP_SCALE)][(int)(x / MMAP_SCALE)].type == ' '
		|| x < 0 || y < 0 || x > world->graphics.mmap_w
		|| y > world->graphics.mmap_h)
		return ;
	world->player.mx = x;
	world->player.my = y;
	render(world);
}

void	move_down(t_cub3d *world)
{
	double	x;
	double	y;

	x = world->player.mx + cos(world->player.angle + M_PI)
		* world->player.move_speed;
	y = world->player.my - sin(world->player.angle + M_PI)
		* world->player.move_speed;
	if (world->graphics.bmp[(int)y][(int)x] == MMAP_WALL
		|| world->graphics.bmp[(int)y][(int)x] == 0x000000
		|| world->graphics.bmp[(int)y][(int)x] == FOV_COLOR
		|| world->map[(int)(y / MMAP_SCALE)][(int)(x / MMAP_SCALE)].type == '1'
		|| world->map[(int)(y / MMAP_SCALE)][(int)(x / MMAP_SCALE)].type == ' '
		|| x < 0 || y < 0 || x > world->graphics.mmap_w
		|| y > world->graphics.mmap_h)
		return ;
	world->player.mx = x;
	world->player.my = y;
	render(world);
}

void	move_left(t_cub3d *world)
{
	double	x;
	double	y;

	x = world->player.mx + cos(world->player.angle + M_PI / 2)
		* world->player.move_speed;
	y = world->player.my - sin(world->player.angle + M_PI / 2)
		* world->player.move_speed;
	if (world->graphics.bmp[(int)y][(int)x] == MMAP_WALL
		|| world->graphics.bmp[(int)y][(int)x] == 0x000000
		|| world->graphics.bmp[(int)y][(int)x] == FOV_COLOR
		|| world->map[(int)(y / MMAP_SCALE)][(int)(x / MMAP_SCALE)].type == '1'
		|| world->map[(int)(y / MMAP_SCALE)][(int)(x / MMAP_SCALE)].type == ' '
		|| x < 0 || y < 0 || x > world->graphics.mmap_w
		|| y > world->graphics.mmap_h)
		return ;
	world->player.mx = x;
	world->player.my = y;
	render(world);
}

void	move_right(t_cub3d *world)
{
	double	x;
	double	y;

	x = world->player.mx + cos(world->player.angle - M_PI / 2)
		* world->player.move_speed;
	y = world->player.my - sin(world->player.angle - M_PI / 2)
		* world->player.move_speed;
	if (world->graphics.bmp[(int)y][(int)x] == MMAP_WALL
		|| world->graphics.bmp[(int)y][(int)x] == 0x000000
		|| world->graphics.bmp[(int)y][(int)x] == FOV_COLOR
		|| world->map[(int)(y / MMAP_SCALE)][(int)(x / MMAP_SCALE)].type == '1'
		|| world->map[(int)(y / MMAP_SCALE)][(int)(x / MMAP_SCALE)].type == ' '
		|| x < 0 || y < 0 || x > world->graphics.mmap_w
		|| y > world->graphics.mmap_h)
		return ;
	world->player.mx = x;
	world->player.my = y;
	render(world);
}
