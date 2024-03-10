/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_destructor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:20:17 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/10 00:33:46 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_destructor(t_cub3d *world)
{
	int		i;

	if (world->map)
	{
		i = 0;
		while (i < world->map_h)
			free(world->map[i++]);
		free(world->map);
	}
	if (world->llmap)
		ft_deldoubly(&world->llmap);
}
