/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:37:28 by woojeong          #+#    #+#             */
/*   Updated: 2022/10/12 16:26:58 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	trans_up(t_point **coord, t_point **o_map, t_img *img)
{
	int		x;
	int		y;

	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			coord[y][x].y_pos -= 40;
			x++;
		}
		y++;
	}
	(img -> move)[y_move] -= 40;
}

void	trans_down(t_point **coord, t_point **o_map, t_img *img)
{
	int		x;
	int		y;

	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			coord[y][x].y_pos += 40;
			x++;
		}
		y++;
	}
	(img -> move)[y_move] += 40;
}

void	trans_right(t_point **coord, t_point **o_map, t_img *img)
{
	int		x;
	int		y;

	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			coord[y][x].x_pos += 40;
			x++;
		}
		y++;
	}
	(img -> move)[x_move] += 40;
}

void	trans_left(t_point **coord, t_point **o_map, t_img *img)
{
	int		x;
	int		y;

	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			coord[y][x].x_pos -= 40;
			x++;
		}
		y++;
	}
	(img -> move)[x_move] -= 40;
}
