/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_img_scale.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:32:03 by woojeong          #+#    #+#             */
/*   Updated: 2022/10/11 15:41:06 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_img_scale(t_point **coord, t_img *img)
{
	double	multiple;

	img -> scale = sqrt(pow(2 * (img -> max_alt), 2) \
			+ pow(sqrt((img -> x_size) * (img -> x_size) \
			+ (img -> y_size) * (img -> y_size)), 2)) + 20;
	multiple = 1;
	while (img -> scale * multiple < 1000)
		multiple += 0.2;
	img -> scale *= multiple;
	change_img_scale(multiple, coord, img);
	return (1);
}

void	change_img_scale(double multiple, t_point **coord, t_img *img)
{
	int	x;
	int	y;
	int	x_origin;
	int	y_origin;

	x_origin = (img -> x_size - 1) / 2;
	y_origin = (img -> y_size - 1) / 2;
	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			coord[y][x].x_pos = (x - x_origin) * multiple;
			coord[y][x].y_pos = (y - y_origin) * multiple;
			coord[y][x].alt *= multiple;
			x++;
		}
		y++;
	}
	(img -> max_alt) *= multiple;
}
