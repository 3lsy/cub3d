/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:38:46 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/09 17:42:21 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// [Note] Every ERROR_MESSAGE, needs to be defined in /includes/libraries.h

/// @fn parse_config - Parse and load the configuration file into our structures
///     The map is loaded in the linked list llmap.
int	load_config(char *file, t_cub3d *world)
{
	// Verify ".cub" extension
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4) != 0)
		exit_error(ECUB);
	parse_config(file, world);
	translate_map(world->llmap, world);
	valid_perimeter(world->map, world->map_h, world->map_w);
	ft_printf("%d\n", 1);
	return (EXIT_SUCCESS);
}

// unknown key, double keys, an invalid path,
// invalid color, invalid map, invalid texture
void	parse_element(char **element, t_cub3d *word)
{
	// Check if the first element is:
	// NO, SO, WE, EA, F, C
	// Check if the texture is valid
	// or Check if the color is valid [0-255,0-255,0-255]
	// word->graphics.ceiling_color = ft_rgb_to_int(r, g, b);
	// On error, call ft_free_split(element) and exit_error();
	// On success, save the element in the structure
	if (element)
	{
		if (element[2])
			exit_error(EINFO);
		if (ft_strcmp(element[0], "NO") == 0 || ft_strcmp(element[0], "SO") == 0 \
			|| ft_strcmp(element[0], "WE") == 0 || ft_strcmp(element[0], "EA") == 0)
			check_nsew(element, word);
		else if (ft_strcmp(element[0], "C") == 0 || ft_strcmp(element[0], "F") == 0)
			check_cf(element, word);
		else
		{
			ft_free_split(&element);
			exit_error(EUNKNOWN);
		}
	}
}


void	parse_map(char *line, t_cub3d *world)
{
	int	size;
	int	i;
	int count;

	size = ft_strlen(line);
	if (size == 0)
		exit_error(EELMAP);
	if (size > world->map_w)
		world->map_w = size;
	// Check if the line is a valid map line
	// On error, exit_error();
	// On success, save the line in the map
	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
			exit_error(EIEMAP);
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			if (count)
				exit_error(EMULP);
			count++;
		}
		i++;
	}
	llmap_append(line, world);
	world->map_h++;
}

int	check_map_started(char *line, t_cub3d *world)
{
	int	i;
	if (world->map_h)
		return (1);
	// Check if the line is the start of the map
	// If it is, world->map_h++;
	i = 0;
	
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && line[i] != ' ')
			return (0);
		i++;
	}
	if (i == (int)ft_strlen(line))
	{
		if (!world->graphics.texture_n || !world->graphics.texture_s || !world->graphics.texture_e \
			|| !world->graphics.texture_w)
			exit_error(EMTEXT);
		if (world->graphics.ceiling_color == -1 || world->graphics.floor_color == -1)
			exit_error(EMCOLOR);
		return (1);
	}
	return (0);
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

	trimmed_line = line;

	trimmed_line = ft_strtrim(line, " ");
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
		parse_element(element, world);
		ft_free_split(&element);
	}
	else
	{
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
	char	*line;
	int		map_end;
	int		player_c;

	map_end = 0;
	world->fd = open(file, O_RDONLY);
	if (world->fd == -1)
		exit_error(strerror(errno));
	world->map_h = 0;
	line = ft_get_next_line(world->fd);
	if (!line)
		exit_error(strerror(errno));
	while (line)
	{
		analyze_line(line, world, &map_end);
		line = ft_get_next_line(world->fd);
	}
	if (!world->map_h)
		exit_error(EMMAP);
	close(world->fd);
	world->fd = -1;
}
