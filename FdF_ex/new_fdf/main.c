/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:34:00 by woojeong          #+#    #+#             */
/*   Updated: 2022/10/12 16:17:19 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

static void	make_img(t_point **coord, t_img *img, t_ptr *ptr, t_point ***o_map);
static void	make_event(t_point **coord, t_point **o_map, t_img *img, t_ptr *p);

int	main(int argc, char *argv[])
{
	t_ptr	ptr;
	t_point	**coord;
	t_point	**o_map;
	t_img	img;

	if (argc != 2)
		argc_err();
	ptr.mlx = mlx_init();
	if (!ptr.mlx)
		mlx_err();
	coord = get_coordinate(argv[1], &img);
	if (img.map_err)
		wrong_map();
	else if (!coord)
		coord_err();
	make_img(coord, &img, &ptr, &o_map);
	ptr.win = mlx_new_window(ptr.mlx, (int)img.scale + 10, \
	(int)img.scale + 10, "fdf");
	if (!ptr.win)
		win_err(coord, o_map, &img);
	mlx_put_image_to_window(ptr.mlx, ptr.win, ptr.img, 10, 10);
	make_event(coord, o_map, &img, &ptr);
}

static void	make_img(t_point **coord, t_img *img, t_ptr *ptr, t_point ***o_map)
{
	get_img_scale(coord, img);
	ptr -> img = mlx_new_image(ptr -> mlx, (int)(img -> scale), \
	(int)(img -> scale));
	img -> addr = mlx_get_data_addr(ptr -> img, &(img -> bits_per_pixel), \
	&(img -> size_line), &(img -> endian));
	*o_map = save_original_map(coord, img);
	if (!(*o_map))
	{
		free_point_arr(coord, img -> y_size);
		perror("zsh");
		exit(1);
	}
	get_img_center_addr(img);
	turn_x(coord, *o_map, img, (3.14 / 4));
	turn_y(coord, *o_map, img, -acos(1 / sqrt(3)));
	draw_img(coord, img);
}

static void	make_event(t_point **coord, t_point **o_map, t_img *img, t_ptr *ptr)
{
	t_param	param;

	param.img = img;
	param.ptr = ptr;
	param.coord = coord;
	param.o_map = o_map;
	mlx_mouse_hook (ptr -> win, mouse_hook, &param);
	mlx_key_hook(ptr -> win, key_hook, &param);
	mlx_loop(ptr -> mlx);
}
