/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:20:48 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/18 12:22:04 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Remove when config is implemented
// Set to 0 if developing config
/// @brief Output of config section
#if 1

// world->graphics.texture_n = load_img();
// ...
int	load_config(char *file __attribute__((unused)), t_cub3d *world)
{
	const char *mapa[] = {
		"       1111111111111111111111111 ",
		"       1000000000110000000000001 ",
		"       1011000001110000000000001 ",
		"       1001000000000000000000001 ",
		"111111111011000001110000000000001",
		"100000000011000001110111110111111",
		"11110111111111011100000010001    ",
		"11110111111111011101010010001    ",
		"11000000110101011100000010001    ",
		"10000000000000001100000010001    ",
		"10000000000000001101010010001    ",
		"11000001110101011111011110N0111  ",
		"11110111 1110101 101111010001    ",
		"11111111 1111111 111111111111    ",
	};

	world->map_h = 14;
	world->map_w = 33;
	world->player.x = 26;
	world->player.y = 11;
	world->graphics.ceiling_color = ft_rgb_to_int(220, 255, 252);
	world->graphics.floor_color = ft_rgb_to_int(180, 95, 6);
	translate_map((char **)mapa, world);
	return (EXIT_SUCCESS);
}

#endif

void	exit_error(char *message)
{
	ft_fprintf(STDERR_FILENO, "Error\n%s\n", message);
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
