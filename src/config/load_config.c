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
	//translate_map(world);
	//if (valid_perimeter(world->map) == EXIT_FAILURE)
	//	exit_error(EPERIMETER);
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
		check_identifier(element, word);
	}
}

void	check_identifier(char **element, t_cub3d *word)
{
	int		width;
	int		height;
	char	**rgb;
	struct stat path_stat;

	if (ft_strcmp(element[0], "NO") == 0)
	{
		ft_printf("%s", "NO\n");
		if (word->graphics.texture_n)
		{
			ft_free_split(&element);
			exit_error(EDUP);
		}
		if (stat(element[1], &path_stat) != 0 || !S_ISREG(path_stat.st_mode)) 
		{
			ft_free_split(&element);
            exit_error(EPATH);
        }
		if (ft_strncmp(element[1] + ft_strlen(element[1]) - 4, ".xpm", 4) != 0)
		{
			ft_free_split(&element);
			exit_error(EEXP);
		}
		word->graphics.texture_n = mlx_xpm_file_to_image(word->graphics.mlx, element[1], &width, &height);
		//ft_printf("w:%d\n", width);
		//ft_printf("h:%d\n", height);
		if (!word->graphics.texture_n)
		{
			ft_printf("%s", "2\n");
			ft_free_split(&element);
			exit_error(EIMG);
		}
	}
	else if (ft_strcmp(element[0], "SO") == 0)
	{
		ft_printf("%s", "SO\n");
		if (word->graphics.texture_s)
		{
			ft_free_split(&element);
			exit_error(EDUP);
		}
		if (stat(element[1], &path_stat) != 0 || !S_ISREG(path_stat.st_mode)) 
		{
			ft_free_split(&element);
            exit_error(EPATH);
        }
		if (ft_strncmp(element[1] + ft_strlen(element[1]) - 4, ".xpm", 4) != 0)
		{
			ft_printf("%s", "1\n");
			ft_free_split(&element);
			exit_error(EEXP);
		}
		word->graphics.texture_s = mlx_xpm_file_to_image(word->graphics.mlx, element[1], &width, &height);
		//ft_printf("w:%d\n", width);
		//ft_printf("h:%d\n", height);
		if (!word->graphics.texture_s)
		{
			ft_printf("%s", "2\n");
			ft_free_split(&element);
			exit_error(EIMG);
		}
	}
	else if (ft_strcmp(element[0], "WE") == 0)
	{
		ft_printf("%s", "WE\n");
		if (word->graphics.texture_w)
		{
			ft_free_split(&element);
			exit_error(EDUP);
		}
		if (stat(element[1], &path_stat) != 0 || !S_ISREG(path_stat.st_mode)) 
		{
			ft_free_split(&element);
            exit_error(EPATH);
        }
		if (ft_strncmp(element[1] + ft_strlen(element[1]) - 4, ".xpm", 4) != 0)
		{
			ft_printf("%s", "1\n");
			ft_free_split(&element);
			exit_error(EEXP);
		}
		word->graphics.texture_w = mlx_xpm_file_to_image(word->graphics.mlx, element[1], &width, &height);
		//ft_printf("w:%d\n", width);
		//ft_printf("h:%d\n", height);
		if (!word->graphics.texture_w)
		{
			ft_printf("%s", "2\n");
			ft_free_split(&element);
			exit_error(EIMG);
		}
	}
	else if (ft_strcmp(element[0], "EA") == 0)
	{
		ft_printf("%s", "EA\n");
		if (word->graphics.texture_e)
		{
			ft_free_split(&element);
			exit_error(EDUP);
		}
		if (stat(element[1], &path_stat) != 0 || !S_ISREG(path_stat.st_mode)) 
		{
			ft_free_split(&element);
            exit_error(EPATH);
        }
		if (ft_strncmp(element[1] + ft_strlen(element[1]) - 4, ".xpm", 4) != 0)
		{
			ft_printf("%s", "1\n");
			ft_free_split(&element);
			exit_error(EEXP);
		}
		word->graphics.texture_e = mlx_xpm_file_to_image(word->graphics.mlx, element[1], &width, &height);
		//ft_printf("w:%d\n", width);
		//ft_printf("h:%d\n", height);
		if (!word->graphics.texture_e)
		{
			ft_printf("%s", "2\n");
			ft_free_split(&element);
			exit_error(EIMG);
		}
	}
	else if (ft_strcmp(element[0], "C") == 0)
	{
		ft_printf("%s", "C\n");
		if (word->graphics.ceiling_color != -1)
		{
			ft_free_split(&element);
			exit_error(EDUP);
		}
		if (element[1])
		{
			rgb = ft_split(element[1], ',');
			if (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255 \
				|| ft_atoi(rgb[1]) < 0 || ft_atoi(rgb[1]) > 255 \
					|| ft_atoi(rgb[2]) < 0 || ft_atoi(rgb[2]) > 255)
			{
				ft_free_split(&rgb);
				ft_free_split(&element);
				exit_error(ECOLOR);
			}
			word->graphics.ceiling_color = ft_rgb_to_int(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
		}
		else
		{
			ft_free_split(&element);
			exit_error(ECOLOR);
		}
	}
	else if (ft_strcmp(element[0], "F") == 0)
	{
		ft_printf("%s", "F\n");
		if (word->graphics.floor_color != -1)
		{
			ft_free_split(&element);
			exit_error(EDUP);
		}
		if (element[1])
		{
			rgb = ft_split(element[1], ',');
			if (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255 \
				|| ft_atoi(rgb[1]) < 0 || ft_atoi(rgb[1]) > 255 \
					|| ft_atoi(rgb[2]) < 0 || ft_atoi(rgb[2]) > 255)
			{
				ft_free_split(&rgb);
				ft_free_split(&element);
				exit_error(ECOLOR);
			}
			word->graphics.floor_color = ft_rgb_to_int(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
		}
		else
		{
			ft_free_split(&element);
			exit_error(ECOLOR);
		}
	}
	else
	{
		ft_free_split(&element);
		exit_error(EUNKNOWN);
	}
}

/*int	parse_map(char *line, t_cub3d *world)
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
}*/

void	check_map_started(char *line, t_cub3d *world)
{
	int	i;
	if (world->map_h)
		return ;
	// Check if the line is the start of the map
	// If it is, world->map_h++;
	i = 0;
	if (!check_empty_line(line))
	{
		while (line[i])
		{
			if (i != '0' && i != '1' && i != 'N' && i != 'S' && i != 'E' && i != 'W' && i != ' ')
				break ;
			i++;
		}
		if (i == (int)ft_strlen(line))
			world->map_h++;
	}
}

int	check_empty_line(char *line)
{
	int i;
	i = 0;
	while (line[0])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
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
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " ");
	if (ft_strlen(trimmed_line) == 0)
	{
		free(trimmed_line);
		return ;
	}
	check_map_started(trimmed_line, world);
	if (!world->map_h)
	{
		element = ft_split(trimmed_line, ' ');
		parse_element(element, world);
		ft_free_split(&element);
	}
	//else
		//parse_map(trimmed_line, world);
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
