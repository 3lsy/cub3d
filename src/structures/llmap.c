/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llmap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:36:12 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/09 16:47:01 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/// @brief Appends a new node to the linked list llmap
void	llmap_append(char *line, t_cub3d *world)
{
	t_doubly	*new;

	new = ft_new_doubly((void *)line, sizeof(char) * (ft_strlen(line) + 1));
	if (!new)
		exit_error(strerror(errno));
	ft_append_doubly(new, &world->llmap);
}
