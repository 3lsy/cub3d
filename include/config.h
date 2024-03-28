/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:10:19 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/09 19:25:11 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "libraries.h"

void	translate_map(char **map, t_cub3d *world);
int	    load_config(char *file, t_cub3d *world);
void	parse_config(char *file, t_cub3d *world);
void	check_nsew(char **element, t_cub3d *word);
void    check_cf(char **element, t_cub3d *word);
int	    check_empty_line(char *line);
void	check_map_started(char *line, t_cub3d *world);
t_img	*load_img(char **element, t_cub3d *world);
void	check_texture(char **element);
void    check_mult_id(char **element, t_cub3d *word);

#endif