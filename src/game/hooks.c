/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 00:42:13 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/10 01:00:30 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_game(void *p __attribute__((unused)))
{
	exit(EXIT_SUCCESS);
}

int	empty_hook(void *p __attribute__((unused)))
{
	return (0);
}
