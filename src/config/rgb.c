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

void	check_number(char **element, int i, int *j, int *rgb)
{
	int	c_size;

	c_size = 0;
	if (element[i][*j] != ',')
	{
		(*rgb)++;
		while (ft_isdigit(element[i][++(*j)]))
			c_size++;
		if (c_size > 3)
			config_error(ENOTNUM, &element, 0);
	}
}

void	check_comma(char **element, t_pair ij, int rgb, int *comma)
{
	if (element[ij.x][ij.y] == ',')
	{
		if ((*comma == 0 && rgb != 1) || (*comma == 1 && rgb != 2)
			|| (*comma == 2 && rgb != 3))
			config_error(ERGBF, &element, 0);
		(*comma)++;
	}
}

int	check_format(char **element)
{
	int	i;
	int	j;
	int	comma;
	int	rgb;

	i = 0;
	comma = 0;
	rgb = 0;
	while (element[++i])
	{
		j = -1;
		while (element[i][++j])
		{
			if (element[i][j] != ',' && !ft_isdigit(element[i][j]))
				config_error(ERGBF, &element, 0);
			check_number(element, i, &j, &rgb);
			if (!element[i][j])
				break ;
			check_comma(element, (t_pair){i, j}, rgb, &comma);
		}
	}
	return (comma);
}
