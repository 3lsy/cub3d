/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:10:19 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/21 20:51:54 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "libraries.h"

int		load_config(char *file, t_cub3d *world);
int		check_map_started(char *trimmed_line, t_cub3d *world);
void	translate_map(t_doubly *llmap, t_cub3d *world);
void	parse_config(char *file, t_cub3d *world);
void	check_nsew(char **element, t_cub3d *word);
void	check_cf(char **element, t_cub3d *word);
void	check_texture(char **element);
void	check_mult_id(char **element, t_cub3d *word);
void	check_outline(t_map **map, int h, int w);
void	flood_fill(t_map **map, int i, int j, t_cub3d *world);
void	valid_perimeter(t_cub3d *world);
void	check_element_missing(char *trimmed_line, t_cub3d *world);
void	check_empty_line(char *trimmed_line, t_cub3d *world, int *map_end);
int		is_empty_file(int fd);
t_img	*load_img(char **element, t_cub3d *world);
void	check_rgb(char **element, int rgb[3]);
int		check_format(char **element);
void	extract_color(char *color, int rgb[3], int *xi, char ***element);

#endif