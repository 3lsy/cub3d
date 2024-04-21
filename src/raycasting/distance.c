/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 20:01:32 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/20 21:12:36 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray_russ(t_player *p)
{
	p->ray.russ[0] = 0;
	p->ray.russ[1] = 0;
	if (0.01 <= p->ray.dir[0] || p->ray.dir[0] <= -0.01)
		p->ray.russ[0] = sqrt(1 + pow(p->ray.dir[1], 2)
				/ pow(p->ray.dir[0], 2));
	if (0.01 <= p->ray.dir[1] || p->ray.dir[1] <= -0.01)
		p->ray.russ[1] = sqrt(1 + pow(p->ray.dir[0], 2)
				/ pow(p->ray.dir[1], 2));
}

void	init_ray_step(t_player *p)
{
	p->ray.hit_axis = -1;
	if (p->ray.dir[0] < 0)
	{
		p->ray.step[0] = -MMAP_SCALE;
		p->ray.len_1d_axis[0] = fmod(p->mx, MMAP_SCALE) * p->ray.russ[0];
	}
	else
	{
		p->ray.step[0] = MMAP_SCALE;
		p->ray.len_1d_axis[0] = (MMAP_SCALE - fmod(p->mx, MMAP_SCALE))
			* p->ray.russ[0];
	}
	if (p->ray.dir[1] < 0)
	{
		p->ray.step[1] = -MMAP_SCALE;
		p->ray.len_1d_axis[1] = fmod(p->my, MMAP_SCALE) * p->ray.russ[1];
	}
	else
	{
		p->ray.step[1] = MMAP_SCALE;
		p->ray.len_1d_axis[1] = (MMAP_SCALE - fmod(p->my, MMAP_SCALE))
			* p->ray.russ[1];
	}
}

// before: return 2 if out of bounds
// now: return 0 if out of bounds
int	found_hit(t_cub3d *world, t_player *p)
{
	if (p->ray.xy[0] >= 0 && p->ray.xy[1] >= 0
		&& p->ray.xy[0] < world->map_w * MMAP_SCALE
		&& p->ray.xy[1] < world->map_h * MMAP_SCALE)
	{
		if (world->map[(int)p->ray.xy[1] / MMAP_SCALE]
			[(int)p->ray.xy[0] / MMAP_SCALE].type == '1')
			return (1);
		else
			return (0);
	}
	return (0);
}

void	walk_on_ray(t_player *p)
{
	if (fabs(p->ray.len_1d_axis[1]) == 0
		|| (p->ray.len_1d_axis[0] < p->ray.len_1d_axis[1]
			&& fabs(p->ray.len_1d_axis[0]) != 0))
	{
		p->ray.xy[0] += p->ray.step[0];
		p->ray.depth = p->ray.len_1d_axis[0];
		p->ray.len_1d_axis[0] += p->ray.russ[0] * MMAP_SCALE;
		p->ray.hit_axis = X_AXIS;
	}
	else
	{
		p->ray.xy[1] += p->ray.step[1];
		p->ray.depth = p->ray.len_1d_axis[1];
		p->ray.len_1d_axis[1] += p->ray.russ[1] * MMAP_SCALE;
		p->ray.hit_axis = Y_AXIS;
	}
}
