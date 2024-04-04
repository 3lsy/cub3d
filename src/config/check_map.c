/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:49:51 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/09 19:24:47 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	translate_map(t_doubly    *llmap, t_cub3d *world)
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

void	valid_perimeter(t_map **map, int h, int w)
{
	// First, verify if every non-space in positions h = 0 and h = h - 1 is a wall
	// Then, verify if every non-space in positions w = 0 and w = w - 1 is a wall
	// If any of these conditions is not met, exit_error() with a descriptive message
	//
	// With flood_fill algorithm, check if the map is surrounded by walls
	// start in every non-visited space and check if it's possible to reach
	// a floor space ('0') from there (if it is possible, exit_error())

	// On the verification inside the positions h = 0, h = h -1, w = 0, w = w - 1
	// Do not verify anything that it is not a space. Every non-visited space
	// Verify with flood_fill.

	int	i;
	int j;

	check_outline(map, h, w);
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			if (map[i][j].type == ' ')
				flood_fill(map, i, j, h, w);
			j++;
		}
		i++;
	}
}

/*
llmap = {
  "11111111 11111 111",
  "     10111000111001",
  "11111001 110111111",
  "101  11    1N01",
  " 1         1001",
  "111111111111111"
}
map = {
	'1','1','1','1','1','1','1','1',' ','1','1','1','1','1',' ','1','1','1',
	' ',' ',' ',' ',' ','1','0','1','1','1','0','0','0','1','1','1','0','0',
	'1','1','1','1','1','0','0','1',' ','1','1','0','1','1','1','1','1','1',
	'1','0','1',' ',' ',' ','1','1',' ',' ',' ','1','N','0','1',' ',' ',' ',
	' ','1',' ',' ',' ',' ',' ',' ',' ',' ',' ','1','0','0','1',' ',' ',' ',
	'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'
}
*/

void	check_outline(t_map **map, int h, int w)
{
	int	i;

	i = 0;
	while (i < w)
	{
		if ((map[0][i].type != ' ' && map[0][i].type != '1') || (map[h - 1][i].type != ' ' && map[h - 1][i].type != '1'))
			exit_error(EWALLO);
		i++;
	}
	i = 1;
	while (i < h - 1)
	{		
		if ((map[i][0].type != ' ' && map[i][0].type != '1') || (map[i][w - 1].type != ' ' && map[i][w - 1].type != '1'))
			exit_error(EWALLI);
		i++;
	}
}

void	flood_fill(t_map **map, int i, int j, int h, int w)
{
	if ((map[i][j].type) == '1' || map[i][j].visited)
		return ;
	map[i][j].visited = 1;
	if ((map[i][j].type) == '0' || (map[i][j].type) == 'N' || (map[i][j].type) == 'S' \
		|| (map[i][j].type) == 'E' || (map[i][j].type) == 'W')
		exit_error(EPERIMETER);
	if (i + 1 < h)
		flood_fill(map, i + 1, j, h, w);
	if (i - 1 >= 0)
		flood_fill(map, i - 1, j, h, w);
	if (j + 1 < w)
		flood_fill(map, i, j + 1, h, w);
	if (j - 1 >= 0)
		flood_fill(map, i, j - 1, h, w);
}