/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:18:00 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/17 01:21:05 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** p->mx/y = player position in mmap
** fmod(p->mx/y, MMAP_SCALE) = player position in cell of mmap
** p->ray.dir = unit vector of player direction
** p->ray.russ = unit step size of player direction (# of cells to move in x/y)
** p->ray.len_1d_axis = len accumul in the ray direction to reach the next cell
*/

void	init_ray(t_player *p)
{
	p->ray.xy[0] = p->mx;
	p->ray.xy[1] = p->my;
	p->ray.dir[0] = cos(p->angle);
	p->ray.dir[1] = -sin(p->angle);
	p->ray.russ[0] = 0;
	p->ray.russ[1] = 0;
	if (0.01 <= p->ray.dir[0] || p->ray.dir[0] <= -0.01)
		p->ray.russ[0] = sqrt(1 + pow(p->ray.dir[1], 2) / pow(p->ray.dir[0], 2));
	if (0.01 <= p->ray.dir[1] || p->ray.dir[1] <= -0.01)
		p->ray.russ[1] = sqrt(1 + pow(p->ray.dir[0], 2) / pow(p->ray.dir[1], 2));

	// dir : left
	if (p->ray.dir[0] < 0)
	{
		p->ray.step[0] = -MMAP_SCALE;
		p->ray.len_1d_axis[0] = fmod(p->mx, MMAP_SCALE) * p->ray.russ[0];
	}
	// dir : right
	else
	{
		p->ray.step[0] = MMAP_SCALE;
		p->ray.len_1d_axis[0] = (MMAP_SCALE - fmod(p->mx, MMAP_SCALE)) * p->ray.russ[0];
	}
	// dir : up
	if (p->ray.dir[1] < 0)
	{
		p->ray.step[1] = -MMAP_SCALE;
		p->ray.len_1d_axis[1] = fmod(p->my, MMAP_SCALE) * p->ray.russ[1];
	}
	// dir : down
	else
	{
		p->ray.step[1] = MMAP_SCALE;
		p->ray.len_1d_axis[1] = (MMAP_SCALE - fmod(p->my, MMAP_SCALE)) * p->ray.russ[1];
	}
}

void	cast_ray(t_cub3d *world, t_player *p, double vray[2])
{
	int		hit;
	double	mdepth;
	double	depth;

	mdepth = MAX_DEPTH * MMAP_SCALE;
	depth = 0;
	hit = 0;
	printf("-- Initial depth: %f - position: %f, %f\n", depth, p->ray.xy[0], p->ray.xy[1]);
	while (!hit && depth < mdepth)
	{
		// walk to next map cell
		if ((p->ray.len_1d_axis[0] < p->ray.len_1d_axis[1] && fabs(p->ray.len_1d_axis[0]) != 0) || fabs(p->ray.len_1d_axis[1]) == 0)
		{
			p->ray.xy[0] += p->ray.step[0];
			depth = p->ray.len_1d_axis[0];
			p->ray.len_1d_axis[0] += p->ray.russ[0] * MMAP_SCALE;
		}
		else
		{
			p->ray.xy[1] += p->ray.step[1];
			depth = p->ray.len_1d_axis[1];
			p->ray.len_1d_axis[1] += p->ray.russ[1] * MMAP_SCALE;
		}
		printf("-- Depth: %f - position: %f, %f\n", depth, p->ray.xy[0], p->ray.xy[1]);
		// check if the ray hit a wall
		// check that ray.xy is in the map
		if (p->ray.xy[0] >= 0 && p->ray.xy[1] >= 0 && p->ray.xy[0] < world->map_w * MMAP_SCALE && p->ray.xy[1] < world->map_h * MMAP_SCALE)
		{
			if (world->map[(int)p->ray.xy[1] / MMAP_SCALE][(int)p->ray.xy[0] / MMAP_SCALE].type == '1')
				hit = 1;
		}
		else
			hit = 2;
	}
	if (hit)
	{
		vray[0] = p->ray.dir[0] * depth;
		vray[1] = p->ray.dir[1] * depth;
		vray[0] += p->mx;
		vray[1] += p->my;
	}
}

void	raycasting(t_cub3d *world)
{
	double	vray[2];

	init_ray(&world->player);
	cast_ray(world, &world->player, vray);
	printf("Mini map pos     x: %f, y: %f\n", world->player.mx, world->player.my);
	printf("Modulus pos      x: %f, y: %f\n", fmod(world->player.mx, MMAP_SCALE), fmod(world->player.my, MMAP_SCALE));
	printf("Unit vector dir  x: %f, y: %f\n", world->player.ray.dir[0], world->player.ray.dir[1]);
	printf("R unit step size x: %f, y: %f\n", world->player.ray.russ[0], world->player.ray.russ[1]);
	printf("Len 1d axis      x: %f, y: %f\n", world->player.ray.len_1d_axis[0], world->player.ray.len_1d_axis[1]);
	printf("Vector ray       x: %f, y: %f\n\n", vray[0], vray[1]);
}
