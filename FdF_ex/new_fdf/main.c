#include "./fdf.h"

int	main(int argc, char *argv[])
{
	t_param	param;
	t_ptr	ptr;
	t_point	**coord;
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
	coord = get_coordinate(argv[1], &img); // malloc : coord
	if (img.map_err)
	{
		write(2, "wrong map\n", 10);
		exit(1);
	}
	else if (!coord)
	{
		perror("zsh");
		exit(1);
	}
	//img
	get_img_scale(coord, &img);
	ptr.img = mlx_new_image(ptr.mlx, img.scale, img.scale);
	img.addr = mlx_get_data_addr(ptr.img, &(img.bits_per_pixel), &(img.size_line), &(img.endian));
	o_map = save_original_map(coord, &img);
	if (!o_map)
	{
		free_point_arr(coord, img.y_size);
		perror("zsh");
		exit(1);
	}
	get_img_center_addr(&img);
	turn_x(coord, o_map, &img, (3.14 / 4));
	turn_y(coord, o_map, &img, -acos(1 / sqrt(3)));
	draw_img(coord, &img);
	//window
	ptr.win = mlx_new_window(ptr.mlx, img.scale + 10, img.scale + 10, "new_title");
	if (!ptr.win)
	{
		free_point_arr(coord, img.y_size);
		free_point_arr(o_map, img.y_size);
		perror("zsh");
		exit(1);
	}
	mlx_put_image_to_window(ptr.mlx, ptr.win, ptr.img, 10, 10);
	// free_point_arr(coord, img.y_size);
	// mlx_destroy_image(ptr.mlx, ptr.img);
	//event
	param.img = &img;
	param.ptr = &ptr;
	param.coord = coord;
	param.o_map = o_map;
	mlx_mouse_hook (ptr.win, mouse_hook, &param);
	mlx_key_hook(ptr.win, key_hook, &param);
	mlx_loop(ptr.mlx);
}

//init_img 함수 만들기

// for (int y = 0; y < img.y_size; y++)
// 	{
// 		for (int x = 0; x < img.x_size; x++)
// 			printf("%0.1f %0.1f / ", o_map[y][x].x_pos, o_map[y][x].y_pos);
// 		printf("\n");
// 	}