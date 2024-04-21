/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:21:32 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/16 18:37:39 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "config.h"
# include "game.h"
# include "raycasting.h"
# include "structures.h"

void	exit_error(char *message);
void	config_error(char *message, char ***element, int i);
t_cub3d	*cub(int action);

#endif