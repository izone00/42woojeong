/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:34:06 by woojeong          #+#    #+#             */
/*   Updated: 2022/10/11 15:34:14 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	turn_right(t_point **coord, t_point **o_map, t_img *img)
{
	turn_x(coord, o_map, img, theta);
	turn_y(coord, o_map, img, 0);
}

void	turn_left(t_point **coord, t_point **o_map, t_img *img)
{
	turn_x(coord, o_map, img, -theta);
	turn_y(coord, o_map, img, 0);
}

void	turn_up(t_point **coord, t_point **o_map, t_img *img)
{
	turn_x(coord, o_map, img, 0);
	turn_y(coord, o_map, img, theta);
}

void	turn_down(t_point **coord, t_point **o_map, t_img *img)
{
	turn_x(coord, o_map, img, 0);
	turn_y(coord, o_map, img, -theta);
}
