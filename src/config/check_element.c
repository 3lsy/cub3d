/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syan <syan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:36:50 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/21 18:05:32 by syan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** [Note] On success or on failure, close the file descriptors
*/

void	check_texture(char **element)
{
	if (ft_strncmp(element[1] + ft_strlen(element[1]) - 4, ".xpm", 4) != 0)
		config_error(EEXP, &element, 1);
}

t_img	*load_img(char **element, t_cub3d *world)
{
	int		height;
	int		width;
	t_img	*img;

	img = mlx_xpm_file_to_image(world->graphics.mlx,
			element[1], &width, &height);
	if (!img)
		config_error(EXPM, &element, 1);
	return (img);
}

void	check_nsew(char **element, t_cub3d *word)
{
	check_mult_id(element, word);
	check_texture(element);
	if (ft_strcmp(element[0], "NO") == 0)
		word->graphics.texture_n = load_img(element, word);
	else if (ft_strcmp(element[0], "SO") == 0)
		word->graphics.texture_s = load_img(element, word);
	else if (ft_strcmp(element[0], "WE") == 0)
		word->graphics.texture_w = load_img(element, word);
	else if (ft_strcmp(element[0], "EA") == 0)
		word->graphics.texture_e = load_img(element, word);
}

void	check_mult_id(char **element, t_cub3d *word)
{
	char	*id;

	id = element[0];
	if ((ft_strcmp(id, "NO") == 0 && word->graphics.texture_n)
		|| (ft_strcmp(id, "SO") == 0 && word->graphics.texture_s)
		|| (ft_strcmp(id, "EA") == 0 && word->graphics.texture_e)
		|| (ft_strcmp(id, "WE") == 0 && word->graphics.texture_w)
		|| (ft_strcmp(id, "C") == 0 && word->graphics.ceiling_color != -1)
		|| (ft_strcmp(id, "F") == 0 && word->graphics.floor_color != -1))
		config_error(EDUP, &element, 0);
}

int	is_empty_file(int fd)
{
	char	buffer[1];
	ssize_t	bytes_read;

	bytes_read = read(fd, buffer, sizeof(buffer));
	if (bytes_read == -1)
		exit_error(strerror(errno));
	return (bytes_read == 0);
}
