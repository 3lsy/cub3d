/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:36:50 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/09 19:27:56 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** [Note] On success or on failure, close the file descriptors
*/

void	check_texture(char **element)
{
    struct stat path_stat;

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
}

t_img	*load_img(char **element, t_cub3d *world)
{
	int height;
    int width;
    t_img   *img;

    img = mlx_xpm_file_to_image(world->graphics.mlx, element[1], &width, &height);
    if (!img)
    {
		ft_free_split(&element);
		exit_error(EIMG);
	}
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

void    check_mult_id(char **element, t_cub3d *word)
{
    if ((ft_strcmp(element[0], "NO") == 0 && word->graphics.texture_n) || \
            (ft_strcmp(element[0], "SO") == 0 && word->graphics.texture_s) || \
                (ft_strcmp(element[0], "EA") == 0 && word->graphics.texture_e) || \
                    (ft_strcmp(element[0], "WE") == 0 && word->graphics.texture_w) || \
                        (ft_strcmp(element[0], "C") == 0 && word->graphics.ceiling_color != -1) || \
                            (ft_strcmp(element[0], "F") == 0 && word->graphics.floor_color != -1))
    {
        ft_free_split(&element);
		exit_error(EDUP);
    }
}

char    **check_rgb(char **element)
{
    char    **rgb;

    if (!element[1])
    {
        ft_free_split(&element);
        exit_error(EMRGB);
    }
    rgb = ft_split(element[1], ',');
    check_digit(rgb, element);
    if (ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255 \
				|| ft_atoi(rgb[1]) < 0 || ft_atoi(rgb[1]) > 255 \
					|| ft_atoi(rgb[2]) < 0 || ft_atoi(rgb[2]) > 255)
	{
		ft_free_split(&rgb);
		ft_free_split(&element);
		exit_error(ECOLOR);
	}
    return (rgb);
}

void    check_digit(char **rgb, char **element)
{
    if (!rgb[0] || !rgb[1] || !rgb[2])
    {
        ft_free_split(&rgb);
        ft_free_split(&element);
        exit_error(EMRGB);
    }
    if ((ft_atoi(rgb[0]) == 0 && ft_strcmp(rgb[0], "0") != 0) \
            || (ft_atoi(rgb[1]) == 0 && ft_strcmp(rgb[1], "0") != 0) \
                || (ft_atoi(rgb[2]) == 0 && ft_strcmp(rgb[2], "0") != 0))
    {
        ft_free_split(&rgb);
        ft_free_split(&element);
        exit_error(EMRGB);
    }
}

void	check_cf(char **element, t_cub3d *word)
{
	char	**rgb;

	check_mult_id(element, word);
	rgb = check_rgb(element);
    //ft_printf("%d\n", ft_atoi(rgb[0]));
    //ft_printf("%d\n", ft_atoi(rgb[1]));
    //ft_printf("%d\n", ft_atoi(rgb[2]));
	if (ft_strcmp(element[0], "C") == 0)
		word->graphics.ceiling_color = ft_rgb_to_int(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
	else if (ft_strcmp(element[0], "F") == 0)
		word->graphics.floor_color = ft_rgb_to_int(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]));
    ft_free_split(&rgb);
}