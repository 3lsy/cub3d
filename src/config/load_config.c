/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syan <syan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:38:46 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/12 16:05:37 by syan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// [Note] Every ERROR_MESSAGE, needs to be defined in /includes/libraries.h

/// @fn parse_config - Parse and load the configuration file into our structures
///     The map is loaded in the linked list llmap.
int	load_config(char *file, t_cub3d *world)
{
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4) != 0)
		exit_error(ECUB);
	parse_config(file, world);
	translate_map(world->llmap, world);
	valid_perimeter(world);
	return (EXIT_SUCCESS);
}

// unknown key, double keys, an invalid path,
// invalid color, invalid map, invalid texture
void	parse_element(char **element, t_cub3d *word)
{
	char	*id;

	if (element)
	{
		if (element[2] && ft_strlen(element[2]) > 0)
			config_error(EINFO, &element, 2);
		id = element[0];
		if (ft_strcmp(id, "NO") == 0 || ft_strcmp(id, "SO") == 0
			|| ft_strcmp(id, "WE") == 0 || ft_strcmp(id, "EA") == 0)
			check_nsew(element, word);
		else if (ft_strcmp(id, "C") == 0 || ft_strcmp(id, "F") == 0)
			check_cf(element, word);
		else
			config_error(EUNKNOWN, &element, 0);
	}
}

void	parse_map(char *line, t_cub3d *world)
{
	int	i;
	int	size;

	size = ft_strlen(line);
	if (size > world->map_w)
		world->map_w = size;
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S'
			&& line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
			exit_error(EIEMAP);
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			if (world->player.x != -1 || world->player.y != -1)
				exit_error(EMULP);
			world->player.x = i;
			world->player.y = world->map_h;
		}
		i++;
	}
	llmap_append(line, world);
	world->map_h++;
}

/*
** [Note] When catching an error, free the local variables 
** before calling exit_error (which calls exit and exit calls the destructor)
*/
/// @brief Analyze the line and check if it's an element or a map
/// @param line The line to analyze
void	analyze_line(char *line, t_cub3d *world, int *map_end)
{
	char	**element;
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " ");
	if (!trimmed_line)
		exit_error(strerror(errno));
	if (ft_strlen(trimmed_line) == 0)
	{
		if (world->map_h && !(*map_end))
			(*map_end) = 1;
		free(trimmed_line);
		return ;
	}
	if (!check_map_started(trimmed_line, world))
	{
		element = ft_split(trimmed_line, ' ');
		free(trimmed_line);
		parse_element(element, world);
		ft_free_split(&element);
	}
	else
	{
		free(trimmed_line);
		if (*map_end)
			exit_error(EMNLE);
		parse_map(line, world);
	}
}

/*
** There are 3 types of lines in the file:
** - 1. [one line]   Elements: NO, SO, WE, EA, F, C
** - 2. [multi-line] Map: must have at least a number 1
** - 3. [one line]   Empty lines
** The map must be the last element in the file
** The map can't have empty lines in between
*/
/// @brief world->map_h is the height of the map
void	parse_config(char *file, t_cub3d *world)
{
	int		map_end;

	map_end = 0;
	world->fd = open(file, O_RDONLY);
	if (world->fd == -1)
		exit_error(strerror(errno));
	world->map_h = 0;
	world->line = ft_get_next_line(world->fd);
	if (!world->line)
		exit_error(strerror(errno));
	while (world->line)
	{
		analyze_line(world->line, world, &map_end);
		free(world->line);
		world->line = ft_get_next_line(world->fd);
	}
	if (!world->map_h)
		exit_error(EMMAP);
	if (world->player.x == -1 && world->player.y == -1)
		exit_error(EMPLAYER);
	close(world->fd);
	world->fd = -1;
}
