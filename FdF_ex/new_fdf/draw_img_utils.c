/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_img_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:31:55 by woojeong          #+#    #+#             */
/*   Updated: 2022/10/11 15:47:39 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_point(t_point *p1, t_point *p2, t_img *img)
{
	if (p1 -> x_pos < -((img -> scale / 2) - 10) \
		|| p1 -> x_pos > ((img -> scale / 2) - 10))
		return (0);
	else if (p1 -> y_pos < -((img -> scale / 2) - 10) \
		|| p1 -> y_pos > ((img -> scale / 2) - 10))
		return (0);
	else if (p2 -> x_pos < -((img -> scale / 2) - 10) \
		|| p2 -> x_pos > ((img -> scale / 2) - 10))
		return (0);
	else if (p2 -> y_pos < -((img -> scale / 2) - 10) \
		|| p2 -> y_pos > ((img -> scale / 2) - 10))
		return (0);
	return (1);
}

void	color_pixel(int x, int y, int color, t_img *img)
{
	char	*img_addr;

	img_addr = img -> center;
	img_addr += y * (img -> size_line);
	img_addr += x * ((img -> bits_per_pixel) / 8);
	if (*(int *)img_addr < color)
		*(int *)img_addr = color;
}

void	get_img_center_addr(t_img *img)
{
	img -> center = img -> addr;
	img -> center += (int)(img -> scale / 2) * (img -> size_line);
	img -> center += (int)(img -> scale / 2) * ((img -> bits_per_pixel) / 8);
}
