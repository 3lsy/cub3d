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

void	check_digit(char **rgb, char **element)
{
	if (!rgb[0] || !rgb[1] || !rgb[2])
	{
		ft_free_split(&rgb);
		config_error(EMRGB, &element, 1);
	}
	if (!ft_isnum(rgb[0]) || !ft_isnum(rgb[1]) || !ft_isnum(rgb[2]))
	{
		ft_free_split(&rgb);
		config_error(ECOLOR, &element, 1);
	}
}

void	check_cf(char **element, t_cub3d *word)
{
	char	**rgb;

	check_mult_id(element, word);
	rgb = check_rgb(element);
	if (ft_strcmp(element[0], "C") == 0)
		word->graphics.ceiling_color = ft_rgb_to_int(ft_atoi(rgb[0]),
				ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	else if (ft_strcmp(element[0], "F") == 0)
		word->graphics.floor_color = ft_rgb_to_int(ft_atoi(rgb[0]),
				ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	ft_free_split(&rgb);
}

int	check_map_started(char *line, t_cub3d *world)
{
	int	i;

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
		check_element_missing(world);
		return (1);
	}
	return (0);
}

void	check_element_missing(t_cub3d *world)
{
	int	missing;

	missing = 0;
	if (!world->graphics.texture_n || !world->graphics.texture_s
		|| !world->graphics.texture_e || !world->graphics.texture_w)
	{
		missing++;
		exit_error(EMTEXT);
	}
	if (world->graphics.ceiling_color == -1
		|| world->graphics.floor_color == -1)
	{
		missing++;
		if (missing == 2)
			exit_error(EMBOTH);
		exit_error(EMCOLOR);
	}
}

void	check_empty_line(char *line, t_cub3d *world, int *map_end)
{
	if (world->map_h && !(*map_end))
		(*map_end) = 1;
	free(line);
}
