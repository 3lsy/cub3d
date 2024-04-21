/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syan <syan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:49:51 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/11 14:58:01 by syan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	translate_map(t_doubly *llmap, t_cub3d *world)
{
	int	i;
	int	j;

	i = 0;
	world->map = ft_calloc(world->map_h, sizeof(t_map *));
	while (i < world->map_h)
	{
		world->map[i] = ft_calloc(world->map_w, sizeof(t_map));
		j = 0;
		while (j < world->map_w)
		{
			if (j >= (int)ft_strlen(((char *)(llmap->obj))))
				world->map[i][j].type = ' ';
			else
				world->map[i][j].type = ((char *)(llmap->obj))[j];
			world->map[i][j].x = j;
			world->map[i][j].y = i;
			world->map[i][j].visited = 0;
			ft_printf("%c ", world->map[i][j].type);
			j++;
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		llmap = llmap->next;
		i++;
	}
}

void	valid_perimeter(t_cub3d *world)
{
	int	i;
	int	j;

	check_outline(world->map, world->map_h, world->map_w);
	i = 0;
	while (i < world->map_h)
	{
		j = 0;
		while (j < world->map_w)
		{
			if (world->map[i][j].type == ' ')
				flood_fill(world->map, i, j, world);
			j++;
		}
		i++;
	}
}

void	check_outline(t_map **map, int h, int w)
{
	int	i;

	i = 0;
	while (i < w)
	{
		if ((map[0][i].type != ' ' && map[0][i].type != '1')
			|| (map[h - 1][i].type != ' ' && map[h - 1][i].type != '1'))
			exit_error(EWALLO);
		i++;
	}
	i = 1;
	while (i < h - 1)
	{
		if ((map[i][0].type != ' ' && map[i][0].type != '1')
			|| (map[i][w - 1].type != ' ' && map[i][w - 1].type != '1'))
			exit_error(EWALLI);
		i++;
	}
}

void	flood_fill(t_map **map, int i, int j, t_cub3d *world)
{
	if ((map[i][j].type) == '1' || map[i][j].visited)
		return ;
	map[i][j].visited = 1;
	if ((map[i][j].type) == '0' || (map[i][j].type) == 'N'
			|| (map[i][j].type) == 'S' || (map[i][j].type) == 'E'
			|| (map[i][j].type) == 'W')
		exit_error(EPERIMETER);
	if (i + 1 < world->map_h)
		flood_fill(map, i + 1, j, world);
	if (i - 1 >= 0)
		flood_fill(map, i - 1, j, world);
	if (j + 1 < world->map_w)
		flood_fill(map, i, j + 1, world);
	if (j - 1 >= 0)
		flood_fill(map, i, j - 1, world);
}
