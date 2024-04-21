/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:20:48 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/21 21:38:50 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(char *message)
{
	ft_fprintf(STDERR_FILENO, "Error\ncub3D: %s\n", message);
	exit(EXIT_FAILURE);
}

void	config_error(char *message, char ***element, int i)
{
	ft_fprintf(STDERR_FILENO, "Error\ncub3D: %s: %s\n", message, (*element)[i]);
	ft_free_split(element);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_cub3d	*world;

	if (ac == 2)
	{
		world = cub(INIT);
		world->graphics.mlx = mlx_init();
		if (!world->graphics.mlx)
			exit_error(EMLX);
		if (load_config(av[1], world) == EXIT_SUCCESS)
			game(world);
	}
	else
		exit_error(USAGE);
	return (EXIT_SUCCESS);
}
