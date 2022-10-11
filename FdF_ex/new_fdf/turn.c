/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:32:59 by woojeong          #+#    #+#             */
/*   Updated: 2022/10/11 15:37:09 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	turn_x(t_point **coord, t_point **o_map, t_img *img, double angle)
{
	static double	pre_angle;
	int				x;
	int				y;

	pre_angle += angle;
	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			coord[y][x].x_pos -= (img -> move)[x_move];
			coord[y][x].y_pos -= (img -> move)[y_move];
			coord[y][x].x_pos = o_map[y][x].x_pos * cos(pre_angle) \
								- o_map[y][x].y_pos * sin(pre_angle);
			coord[y][x].y_pos = o_map[y][x].x_pos * sin(pre_angle) \
								+ o_map[y][x].y_pos * cos(pre_angle);
			x++;
		}
		y++;
	}
}

void	turn_y(t_point **coord, t_point **o_map, t_img *img, double angle)
{
	static double	pre_angle;
	int				x;
	int				y;
	double			pre_x;
	double			pre_y;

	y = 0;
	pre_angle += angle;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			coord[y][x].y_pos = (coord[y][x].y_pos) * cos(pre_angle);
			coord[y][x].y_pos += coord[y][x].alt * (sin(pre_angle));
			coord[y][x].x_pos += (img -> move)[x_move];
			coord[y][x].y_pos += (img -> move)[y_move];
			x++;
		}
		y++;
	}	
}
