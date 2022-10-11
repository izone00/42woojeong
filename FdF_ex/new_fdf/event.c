/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:31:59 by woojeong          #+#    #+#             */
/*   Updated: 2022/10/11 17:02:37 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
// right: 124 down:125 left :123 up:126
// w:13 a:0 s:1 d:2
void	key_event(int keycode, t_point **coord, t_point **o_map, t_img *img)
{
	if (keycode == 124)
		turn_right(coord, o_map, img);
	else if (keycode == 123)
		turn_left(coord, o_map, img);
	else if (keycode == 126)
		turn_up(coord, o_map, img);
	else if (keycode == 125)
		turn_down(coord, o_map, img);
	else if (keycode == 13)
		trans_up(coord, o_map, img);
	else if (keycode == 1)
		trans_down(coord, o_map, img);
	else if (keycode == 0)
		trans_left(coord, o_map, img);
	else if (keycode == 2)
		trans_right(coord, o_map, img);
}

void	esc_event(t_ptr *ptr, t_point **coord, t_point **o_map, t_img *img)
{
	free_point_arr(coord, img -> y_size);
	free_point_arr(o_map, img -> y_size);
	mlx_destroy_image(ptr -> mlx, ptr -> img);
	mlx_clear_window(ptr -> mlx, ptr -> win);
	mlx_destroy_window(ptr -> mlx, ptr -> win);
	exit(0);
}

int	key_hook(int keycode, void *param)
{
	t_ptr	*ptr;
	t_img	*img;
	t_point	**coord;
	t_point	**o_map;
	int		i;

	ptr = ((t_param *)param)-> ptr;
	img = ((t_param *)param)-> img;
	coord = ((t_param *)param)-> coord;
	o_map = ((t_param *)param)-> o_map;
	if ((keycode >= 123 && keycode <= 126) || keycode == 13 || (keycode <= 2 && keycode >= 0))
	{
		while (i < ((int)img -> scale) * ((int)img -> scale) * 4)
			(img -> addr)[i++] = 0x00;
		mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img, 10, 10);
		key_event(keycode, coord, o_map, img);
		draw_img(coord, img);
		mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img, 10, 10);
	}
	else if (keycode == 53)
		esc_event(ptr, coord, o_map, img);
	return (1);
}

int	mouse_hook(int button, int x, int y, void *param)
{
	t_ptr	*ptr;
	t_img	*img;
	t_point	**coord;
	t_point	**o_map;
	int		i;

	ptr = ((t_param *)param)-> ptr;
	img = ((t_param *)param)-> img;
	coord = ((t_param *)param)-> coord;
	o_map = ((t_param *)param)-> o_map;
	(void)x;
	(void)y;
	i = 0;
	while (i < ((int)(img -> scale)) * ((int)(img -> scale)) * 4)
		(img -> addr)[i++] = 0x00;
	mlx_put_image_to_window(ptr -> mlx, ptr -> win, ptr -> img, 10, 10);
	if (button == 4)
		zoom_in(coord, o_map, img);
	else if (button == 5)
		zoom_out(coord, o_map, img);
	draw_img(coord, img);
	mlx_put_image_to_window(ptr -> mlx, ptr -> win, ptr -> img, 10, 10);
	return (1);
}
