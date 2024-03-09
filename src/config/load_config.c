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
	parse_config(file, world);
	translate_map(world);
	if (valid_perimeter(world->map) == EXIT_FAILURE)
		exit_error(EPERIMETER);
	return (EXIT_SUCCESS);
}

// unknown key, double keys, an invalid path,
// invalid color, invalid map, invalid texture
int	parse_element(char **element, t_cub3d *word)
{
	// Check if the first element is:
	// NO, SO, WE, EA, F, C
	// Check if the texture is valid
	// or Check if the color is valid [0-255,0-255,0-255]
	// word->graphics.ceiling_color = ft_rgb_to_int(r, g, b);
	// On error, call ft_free_split(element) and exit_error();
	// On success, save the element in the structure
}

int	parse_map(char *line, t_cub3d *world)
{
	int	size;

	size = ft_strlen(line);
	if (size == 0)
		exit_error(EELMAP);
	if (size > world->map_w)
		world->map_w = size;
	// Check if the line is a valid map line
	// On error, exit_error();
	// On success, save the line in the map
	llmap_append(line, world);
	world->map_h++;
}

void	check_map_started(char *line, t_cub3d *world)
{
	if (world->map_h)
		return ;
	// Check if the line is the start of the map
	// If it is, world->map_h++;
}

/*
** [Note] When catching an error, free the local variables 
** before calling exit_error (which calls exit and exit calls the destructor)
*/
/// @brief Analyze the line and check if it's an element or a map
/// @param line The line to analyze
void	analyze_line(char *line, t_cub3d *world)
{
	char	**element;

	check_map_started(line, world);
	if (!world->map_h)
	{
		element = ft_split(line, ' ');
		parse_element(element, world);
		ft_free_split(element);
	}
	else
		parse_map(line, world);
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

	world->fd = open(file, O_RDONLY);
	if (world->fd == -1)
		exit_error(strerror(errno));
	world->map_h = 0;
	line = ft_get_next_line(world->fd);
	if (!line)
		exit_error(strerror(errno));
	while (line)
	{
		analyze_line(line, world);
		line = ft_get_next_line(world->fd);
		if (!line)
			exit_error(strerror(errno));
	}
	close(world->fd);
	world->fd = -1;
}
