/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_config_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:28:03 by syan              #+#    #+#             */
/*   Updated: 2024/04/21 20:52:09 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_cf(char **element, t_cub3d *word)
{
	int	rgb[3];

	rgb[0] = -1;
	rgb[1] = -1;
	rgb[2] = -1;
	check_mult_id(element, word);
	check_rgb(element, rgb);
	if (ft_strcmp(element[0], "C") == 0)
		word->graphics.ceiling_color = ft_rgb_to_int(rgb[0], rgb[1], rgb[2]);
	else if (ft_strcmp(element[0], "F") == 0)
		word->graphics.floor_color = ft_rgb_to_int(rgb[0], rgb[1], rgb[2]);
}

int	check_map_started(char *trimmed_line, t_cub3d *world)
{
	int		i;
	char	*line;

	line = trimmed_line;
	if (world->map_h)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != ' ')
			return (0);
		i++;
	}
	if (i == (int)ft_strlen(line))
	{
		check_element_missing(trimmed_line, world);
		return (1);
	}
	return (0);
}

void	check_element_missing(char *trimmed_line, t_cub3d *world)
{
	int	missing;

	missing = 0;
	if (!world->graphics.texture_n || !world->graphics.texture_s
		|| !world->graphics.texture_e || !world->graphics.texture_w)
		missing++;
	if (world->graphics.ceiling_color == -1
		|| world->graphics.floor_color == -1)
	{
		free(trimmed_line);
		missing++;
		if (missing == 2)
			exit_error(EMBOTH);
		exit_error(EMCOLOR);
	}
	else if (missing == 1)
	{
		free(trimmed_line);
		exit_error(EMTEXT);
	}
}

void	check_empty_line(char *trimmed_line, t_cub3d *world, int *map_end)
{
	if (world->map_h && !(*map_end))
		(*map_end) = 1;
	free(trimmed_line);
}

void	check_rgb(char **element, int rgb[3])
{
	int	i;
	int	xi;
	int	comma;

	if (!element[1])
		config_error(EMRGB, &element, 0);
	comma = check_format(element);
	if (comma != 2)
		config_error(EMCOMMAS, &element, 0);
	xi = 0;
	i = 0;
	comma = 0;
	while (element[++i])
	{
		if (ft_strcmp(element[i], ",") == 0)
			continue ;
		extract_color(element[i], rgb, &xi, &element);
	}
	if (xi != 3)
		config_error(EMRGB, &element, 0);
}
