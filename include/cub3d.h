/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:21:32 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/09 18:54:19 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "config.h"
# include "game.h"
# include "raycasting.h"

void	exit_error(char *message);
t_cub3d	*cub(int action);
void	ft_destructor(t_cub3d *world);
void	graphic_destructor(t_graphics *graphics);
void	map_destructor(t_cub3d *world);

#endif