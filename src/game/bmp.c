/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:17:17 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/18 21:24:28 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	has_floor(char t, t_player *player)
{
	if (t == 'N' || t == 'S' || t == 'W' || t == 'E' || t == '0')
	{
		if (t == '0')
			return (FLOOR);
		if (t == 'N')
			player->angle = M_PI / 2;
		if (t == 'S')
			player->angle = 3 * M_PI / 2;
		if (t == 'W')
			player->angle = M_PI;
		if (t == 'E')
			player->angle = 0;
		return (PLAYER);
	}
	return (0);
}

/*
** Square:
if (p.mx - p.diameter / 2 < x && x < p.mx + p.diameter / 2)
{
	if (p.my - p.diameter / 2 < y && y < p.my + p.diameter / 2)
		return (1);
}
return (0);
*/
int	is_player(t_player p, int x, int y)
{
	if (pow(p.diameter / 2, 2) > pow(p.mx - x, 2) + pow(p.my - y, 2))
		return (1);
	return (0);
}

// if (map[m.y / MMAP_SCALE][m.x / MMAP_SCALE].type == ' ')
// (*bmp)[m.y][m.x] = 0x00ff00; // test for update map
void	paint_bmp(int ***bmp, t_pair m, t_player *player, t_map **map)
{
	int	w;
	int	p;

	w = m.x;
	while (m.y-- > 0)
	{
		m.x = w;
		while (m.x-- > 0)
		{
			if (map[m.y / MMAP_SCALE][m.x / MMAP_SCALE].type == '1')
				(*bmp)[m.y][m.x] = MMAP_WALL;
			p = has_floor(map[m.y / MMAP_SCALE][m.x / MMAP_SCALE].type, player);
			if (p == FLOOR || (p == PLAYER && !is_player(*player, m.x, m.y)))
				(*bmp)[m.y][m.x] = MMAP_FLOOR;
			else if (p == PLAYER)
				(*bmp)[m.y][m.x] = PLAYER_COLOR;
			if (is_arrow(*player, m.x, m.y))
				(*bmp)[m.y][m.x] = ARROW_COLOR;
		}
	}
}

static void	init_dimensions(t_graphics *graphics, t_cub3d *world)
{
	graphics->mmap_w = world->map_w * MMAP_SCALE;
	graphics->mmap_h = world->map_h * MMAP_SCALE;
	world->player.mx = MMAP_SCALE * (world->player.x + 0.5);
	world->player.my = MMAP_SCALE * (world->player.y + 0.5);
}

void	new_bmp(t_graphics *graphics, t_cub3d *world)
{
	init_dimensions(graphics, world);
	graphics->bmp = bmp_square(graphics->mmap_w, graphics->mmap_h,
			graphics->ceiling_color);
	paint_bmp(&graphics->bmp, (t_pair){graphics->mmap_w, graphics->mmap_h},
		&world->player, world->map);
	world->map[(int)world->player.y][(int)world->player.x].type = '0';
}
