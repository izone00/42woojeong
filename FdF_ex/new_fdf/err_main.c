/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:13:02 by woojeong          #+#    #+#             */
/*   Updated: 2022/10/12 16:18:09 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

void	argc_err(void)
{
	write(2, "argv err", 8);
	exit(1);
}

void	mlx_err(void)
{
	perror("zsh");
	exit(1);
}

void	wrong_map(void)
{
	write(2, "wrong map\n", 10);
	exit(1);
}

void	coord_err(void)
{
	perror("zsh");
	exit(1);
}

void	win_err(t_point **coord, t_point **o_map, t_img *img)
{
	free_point_arr(coord, img -> y_size);
	free_point_arr(o_map, img -> y_size);
	perror("zsh");
	exit(1);
}
