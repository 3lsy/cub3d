/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:39:40 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/10 14:40:39 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "libraries.h"

/*
** Map
*/

void	free_bmp(int ***bmp, int h);
void	new_bmp(t_graphics *graphics, t_cub3d *world);

/*
** Destructors
*/

void	ft_destructor(t_cub3d *world);
void	graphic_destructor(t_graphics *graphics);
void	map_destructor(t_cub3d *world);

#endif