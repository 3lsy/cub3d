/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 12:17:29 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/17 18:19:13 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "libraries.h"

void	init_ray(t_player *p, double angle);
void	raycasting(t_cub3d *world);
void	new_bmp_3d(t_graphics *graphics, t_cub3d *word);
void	paint_strip(t_graphics *graphics, t_player *p, int x);
void	paint_3d(t_cub3d *world);

#endif