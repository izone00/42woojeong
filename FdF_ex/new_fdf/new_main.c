
#include "./fdf.h"


int key_hook(int keycode, void *param);

int	main(int argc, char *argv[])
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	t_point	**axis;
	t_img	img;
	void	*param;

	//argv err
	if (argc != 2)
	{
		write(2, "argv err", 8);
		exit(1);
	}
	//init
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
	{
		perror("zsh");
		exit(1);
	}
	//parse
	axis = get_map_axis(argv[1], &img); // malloc
	if (!axis)
		exit(1);
	// for (int y = 0; y < img.y_size; y++)
	// {
	// 	for (int x = 0; axis[y][x].x_pos >= 0; x++)
	// 		printf("[%.0f,%.0f,%.0f]", axis[y][x].x_pos, axis[y][x].y_pos, axis[y][x].alt);
	// 	printf("\n");
	// }
	//img
	// change_img_scale(axis);
	get_img_size(axis, &img);// x_size에 관한 상황을 처리
	img_ptr = mlx_new_image(mlx_ptr, img.width, img.height);
	img.addr = mlx_get_data_addr(img_ptr, &(img.bits_per_pixel), &(img.size_line), &(img.endian));
	draw_img(axis, &img);
	// //window
	win_ptr = mlx_new_window(mlx_ptr, img.width*2, img.height*2, "new_title");
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 10, 10);
	// //event
	// mlx_key_hook(win_ptr, key_hook, param);
	mlx_loop(mlx_ptr);
}

