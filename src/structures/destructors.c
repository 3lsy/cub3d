/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destructors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:40:22 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/10 14:18:36 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// [Not implemented] - map_destructor
void	ft_destructor(t_cub3d *world)
{
	if (world->fd != -1)
		close(world->fd);
	if (world->line)
		free(world->line);
	map_destructor(world);
	graphic_destructor(&world->graphics);
}

static __attribute__((destructor)) void	destructor(void)
{
	ft_get_next_line(FREE_BUFFER);
	cub(DESTRUCTOR);
}
