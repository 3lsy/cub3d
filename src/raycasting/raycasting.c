/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echavez- <echavez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:18:00 by echavez-          #+#    #+#             */
/*   Updated: 2024/03/14 10:39:16 by echavez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
void raycasting()
{
	wall_distance();
}

void	wall_distance(t_player *player, t_pair m)
{
	
}
*/

/*
** First, the distance of the arrow must be the size of p.diameter.
** d[2]: Translated unitary vector to the center of the player.
**       resize the vector to the size of the arrow (p.diameter).
** m:    Slope of the arrow between the center of the player and the arrow.
** Slope: To verify if the point x,y is in the slope of the arrow, 
**        we use the equation of the line.
**        y - y1 = m(x - x1)
**		(y - p.my) - m(x - p.mx) < ARROW_W
**		(y - p.my) - m(x - p.mx) > -ARROW_W
**		(x - p.mx) - (y - p.my) / m < ARROW_W
**		(x - p.mx) - (y - p.my) / m > -ARROW_W
** mx: Center of the player in x in the minimap.
** my: Center of the player in y in the minimap.
*/
/// @brief Direction of the player. Arrow.
int	is_arrow(t_player p, int x, int y)
{
	double	d[2];
	double	m;

	if (pow(ARROW_LEN, 2) > pow(p.mx - x, 2) + pow(p.my - y, 2))
	{
		d[0] = cos(p.angle) * ARROW_LEN + p.mx;
		d[1] = -sin(p.angle) * ARROW_LEN + p.my;
		if (pow(ARROW_LEN - p.diameter / 2, 2)
			< pow(d[0] - x, 2) + pow(d[1] - y, 2))
			return (0);
		if (d[0] == p.mx && p.mx - ARROW_W < x && x < p.mx + ARROW_W)
			return (1);
		m = (d[1] - p.my) / (d[0] - p.mx);
		if (((y - p.my) - m * (x - p.mx) < ARROW_W
				&& (y - p.my) - m * (x - p.mx) > -ARROW_W)
			|| ((x - p.mx) - (y - p.my) / m < ARROW_W
				&& (x - p.mx) - (y - p.my) / m > -ARROW_W))
			return (1);
	}
	return (0);
}
