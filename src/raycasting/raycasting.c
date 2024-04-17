/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:18:00 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/17 18:13:18 by echavez-         ###   ########.fr       */
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

double	cast_ray(t_cub3d *world, t_player *p)
{
	int		hit;
	double	mdepth;
	double	depth;

	mdepth = MAX_DEPTH * MMAP_SCALE;
	depth = 0;
	hit = 0;
	while (!hit && depth < mdepth)
	{
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
		p->ray.vray[0] = p->ray.dir[0] * depth;
		p->ray.vray[1] = p->ray.dir[1] * depth;
		p->ray.vray[0] += p->mx;
		p->ray.vray[1] += p->my;
	}
	return (depth);
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
		p->ray.depth = cast_ray(world, p);
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
