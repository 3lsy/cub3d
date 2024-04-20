/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:20:48 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/20 18:28:53 by echavez-         ###   ########.fr       */
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
	int b;
	//creation of the textures images
	world->graphics.texture_n = mlx_xpm_file_to_image(world->graphics.mlx,
			"textures/north_wall/crystal_box.xpm", &b, &b);
	world->graphics.texture_s = mlx_xpm_file_to_image(world->graphics.mlx,
			"textures/south_wall/crystal_imac.xpm", &b, &b);
	world->graphics.texture_w = mlx_xpm_file_to_image(world->graphics.mlx,
			"textures/west_wall/crystal_sign.xpm", &b, &b);
	world->graphics.texture_e = mlx_xpm_file_to_image(world->graphics.mlx,
			"textures/east_wall/crystal.xpm", &b, &b);
	//creation of the textures bitmaps
	world->graphics.texture_n_bmp = bmp_square(world->graphics.texture_n->width,
			world->graphics.texture_n->height, 0x000000);
	world->graphics.texture_s_bmp = bmp_square(world->graphics.texture_s->width,
			world->graphics.texture_s->height, 0x000000);
	world->graphics.texture_w_bmp = bmp_square(world->graphics.texture_w->width,
			world->graphics.texture_w->height, 0x000000);
	world->graphics.texture_e_bmp = bmp_square(world->graphics.texture_e->width,
			world->graphics.texture_e->height, 0x000000);
	//conversion of the textures to bitmaps
	img_to_bmp(world->graphics.texture_n, world->graphics.texture_n_bmp);
	img_to_bmp(world->graphics.texture_s, world->graphics.texture_s_bmp);
	img_to_bmp(world->graphics.texture_w, world->graphics.texture_w_bmp);
	img_to_bmp(world->graphics.texture_e, world->graphics.texture_e_bmp);
	// world->graphics.texture_w = new_img(world->graphics.mlx, w, h,
	// 		world->graphics.texture_n_bmp);
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
