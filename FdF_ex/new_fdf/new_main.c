
#include "./fdf.h"


int	main(int argc, char *argv[])
{
	t_pen	pen;
	t_ptr	ptr;
	t_point	**axis;
	t_point	**o_map;
	t_img	img;

	//argv err
	if (argc != 2)
	{
		write(2, "argv err", 8);
		exit(1);
	}
	//init
	ptr.mlx = mlx_init();
	if (!ptr.mlx)
	{
		perror("zsh");
		exit(1);
	}
	//parse
	axis = get_map_axis(argv[1], &img); // malloc
	if (!axis)
		exit(1);
	//img
	get_img_size(axis, &img);
	// ft_printf("x_size : %d, y_size : %d\n", img.x_origin, img.y_origin);
	// change_img_scale(axis, &img);
	ptr.img = mlx_new_image(ptr.mlx, img.scale, img.scale);
	img.addr = mlx_get_data_addr(ptr.img, &(img.bits_per_pixel), &(img.size_line), &(img.endian));
	o_map = save_original_map(axis, &img);
	get_img_origin(&img);
	turn_x(axis, o_map, &img, (3.14 / 4));
	turn_y(axis, o_map, &img, -acos(1 / sqrt(3)));
	draw_img(axis, &img);
	//window
	ptr.win = mlx_new_window(ptr.mlx, img.scale + 10, img.scale + 10, "new_title");
	mlx_put_image_to_window(ptr.mlx, ptr.win, ptr.img, 10, 10);
	// free
	// free_point_arr(axis, img.y_size);
	// mlx_destroy_image(ptr.mlx, ptr.img);
	//event
	pen.img = &img;
	pen.ptr = &ptr;
	pen.axis = axis;
	pen.o_map = o_map;
	mlx_mouse_hook (ptr.win, mouse_hook, &pen);
	mlx_key_hook(ptr.win, rotate_key_hook, &pen);
	// mlx_key_hook(ptr.win, esc_key_hook, &ptr);
	mlx_loop(ptr.mlx);
}

//init_img 함수 만들기

// for (int y = 0; y < img.y_size; y++)
// 	{
// 		for (int x = 0; x < img.x_size; x++)
// 			printf("%0.1f %0.1f / ", o_map[y][x].x_pos, o_map[y][x].y_pos);
// 		printf("\n");
// 	}