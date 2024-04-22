/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:36:11 by echavez-          #+#    #+#             */
/*   Updated: 2024/04/21 00:17:23 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	throw_rgb_error(char *e, char ***c, char ***element)
{
	if (*c)
		ft_free_split(c);
	config_error(e, element, 0);
}

void	extract_color(char *color, int rgb[3], int *xi, char ***element)
{
	char	**c;
	int		i;
	int		num;

	c = ft_split(color, ',');
	if (!c)
		throw_rgb_error(strerror(errno), NULL, element);
	i = -1;
	while (c[++i])
	{
		if (!ft_isnum(c[i]) || ft_strlen(c[i]) > 3)
			throw_rgb_error(ENOTNUM, &c, element);
		num = ft_atoi(c[i]);
		if (num < 0 || num > 255)
			throw_rgb_error(ENOTNUM, &c, element);
		if (*xi > 2)
			throw_rgb_error(ERGBF, &c, element);
		rgb[(*xi)++] = num;
	}
	ft_free_split(&c);
}

void	check_rgb(char **element, int rgb[3])
{
	int	i;
	int	xi;
	int	comma;

	if (!element[1])
		config_error(EMRGB, &element, 0);
	xi = 0;
	i = 0;
	comma = 0;
	while (element[++i])
	{
		comma += ft_strchr_len(element[i], ',');
		if (comma > 2)
			config_error(EMCOMMAS, &element, 0);
		if (ft_strcmp(element[i], ",") == 0)
			continue ;
		extract_color(element[i], rgb, &xi, &element);
	}
	if (xi != 3)
		config_error(EMRGB, &element, 0);
	if (comma != 2)
		config_error(EMCOMMAS, &element, 0);
}
