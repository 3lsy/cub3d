/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:18:00 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/17 20:04:38 by echavez-         ###   ########.fr       */
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
void	init_ray(t_player *p, double angle)
{
	p->ray.xy[0] = p->mx;
	p->ray.xy[1] = p->my;
	p->ray.dir[0] = cos(angle);
	p->ray.dir[1] = -sin(angle);
	init_ray_russ(p);
	init_ray_step(p);
}

void	cast_ray(t_cub3d *world, t_player *p)
{
	int		hit;
	double	mdepth;

	mdepth = MAX_DEPTH * MMAP_SCALE;
	p->ray.depth = 0;
	hit = 0;
	while (!hit && p->ray.depth < mdepth)
	{
		walk_on_ray(p);
		hit = found_hit(world, p);
	}
	if (hit)
	{
		p->ray.vray[0] = p->ray.dir[0] * p->ray.depth;
		p->ray.vray[1] = p->ray.dir[1] * p->ray.depth;
		p->ray.vray[0] += p->mx;
		p->ray.vray[1] += p->my;
	}
}

void	paint_ray(t_cub3d *world, double vray[2])
{
	world->graphics.bmp[(int)vray[1]][(int)vray[0]] = FOV_COLOR;
	world->graphics.bmp[(int)vray[1] + 1][(int)vray[0]] = FOV_COLOR;
	world->graphics.bmp[(int)vray[1] - 1][(int)vray[0]] = FOV_COLOR;
	world->graphics.bmp[(int)vray[1]][(int)vray[0] + 1] = FOV_COLOR;
	world->graphics.bmp[(int)vray[1]][(int)vray[0] - 1] = FOV_COLOR;
	world->graphics.bmp[(int)vray[1] + 2][(int)vray[0]] = FOV_COLOR;
	world->graphics.bmp[(int)vray[1] - 2][(int)vray[0]] = FOV_COLOR;
	world->graphics.bmp[(int)vray[1]][(int)vray[0] + 2] = FOV_COLOR;
	world->graphics.bmp[(int)vray[1]][(int)vray[0] - 2] = FOV_COLOR;
}

/*
** FOV
*/
void	cast_fov(t_cub3d *world, t_player *p)
{
	double	fov_rad;
	double	angle_iterator;
	int	i;

	fov_rad = FOV * (M_PI / 180);
	angle_iterator = p->angle - fov_rad / 2;
	i = 0;
	while (angle_iterator <= p->angle + fov_rad / 2)
	{
		init_ray(p, angle_iterator);
		cast_ray(world, p);
		paint_ray(world, p->ray.vray);
		paint_strip(&world->graphics, p, i * STRIP_W);
		angle_iterator += ANGLE_UNIT * M_PI;
		i++;
	}
}

void	raycasting(t_cub3d *world)
{
	int	y;
	int	x;

	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			world->graphics.bmp_3d[y][x] = 0x000000;
			x++;
		}
		y++;
	}
	cast_fov(world, &world->player);
}
