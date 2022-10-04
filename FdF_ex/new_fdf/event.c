#include "fdf.h"
// right: 124 down:125 left :123 up:126
// w:13 a:0 s:1 d:2
int	rotate_key_hook(int keycode, void *pen)
{
	t_ptr	*ptr;
	t_img	*img;
	t_point	**axis;
	t_point	**o_map;

	ptr = ((t_pen *)pen) -> ptr;
	img = ((t_pen *)pen) -> img;
	axis = ((t_pen *)pen) -> axis;
	o_map = ((t_pen *)pen) -> o_map;
	for (int i = 0; i < (img -> scale) * (img -> scale) * 4; i++)
		(img -> addr)[i] = 0x00;
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img, 10, 10);
	if (keycode == 124)
		turn_right(axis, o_map, img);
	else if (keycode == 123)
		turn_left(axis, o_map, img);
	else if (keycode == 126)
		turn_up(axis, o_map, img);
	else if (keycode == 125)
		turn_down(axis, o_map, img);
	else if (keycode == 13)
		trans_up(axis, o_map, img);
	else if (keycode == 1)
		trans_down(axis, o_map, img);
	else if (keycode == 0)
		trans_left(axis, o_map, img);
	else if (keycode == 2)
		trans_right(axis, o_map, img);
	draw_img(axis, img);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img, 10, 10);
	if (keycode == 53)
	{
		mlx_clear_window(ptr -> mlx, ptr -> win);
		mlx_destroy_window(ptr -> mlx, ptr -> win);
		exit(0);
	}
	return (1);
}

void	zoom_in(void *pen)
{
	t_ptr	*ptr;
	t_img	*img;
	t_point	**axis;
	t_point	**o_map;
	int		x;
	int		y;

	ptr = ((t_pen *)pen) -> ptr;
	img = ((t_pen *)pen) -> img;
	axis = ((t_pen *)pen) -> axis;
	o_map = ((t_pen *)pen) -> o_map;
	for (int i = 0; i < (img -> scale) * (img -> scale) * 4; i++)
			(img -> addr)[i] = 0x00;
	mlx_put_image_to_window(ptr -> mlx, ptr -> win, ptr -> img, 10, 10);
	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			axis[y][x].x_pos *= 1.2;
			axis[y][x].y_pos *= 1.2;
			axis[y][x].alt *= 1.2;
			o_map[y][x].x_pos *= 1.2;
			o_map[y][x].y_pos *= 1.2;
			o_map[y][x].alt *= 1.2;
			// printf("[%.1f, %.1f] ", axis[y][x].x_pos, axis[y][x].y_pos);
			x++;
		}
		// printf("\n");
		y++;
	}
	(img -> max_alt) *= 1.2;
	draw_img(axis, img);
		mlx_put_image_to_window(ptr -> mlx, ptr -> win, ptr -> img, 10, 10);
}
void	zoom_out(void *pen)
{
	t_ptr	*ptr;
	t_img	*img;
	t_point	**axis;
	t_point	**o_map;
	int		x;
	int		y;

	ptr = ((t_pen *)pen) -> ptr;
	img = ((t_pen *)pen) -> img;
	axis = ((t_pen *)pen) -> axis;
	o_map = ((t_pen *)pen) -> o_map;
	for (int i = 0; i < (img -> scale) * (img -> scale) * 4; i++)
		(img -> addr)[i] = 0x00;
	mlx_put_image_to_window(ptr -> mlx, ptr -> win, ptr -> img, 10, 10);
	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			axis[y][x].x_pos /= 1.2;
			axis[y][x].y_pos /= 1.2;
			axis[y][x].alt /= 1.2;
			o_map[y][x].x_pos /= 1.2;
			o_map[y][x].y_pos /= 1.2;
			o_map[y][x].alt /= 1.2;
			// printf("[%.1f, %.1f] ", axis[y][x].x_pos, axis[y][x].y_pos);
			x++;
		}
		// printf("\n");
		y++;
	}
	(img -> max_alt) /= 1.2;
	draw_img(axis, img);
		mlx_put_image_to_window(ptr -> mlx, ptr -> win, ptr -> img, 10, 10);
}
int	mouse_hook(int button, int x,int y, void *pen)
{
	// ft_printf("button : %d, [%d,%d]\n", button, x, y);
	(void)x;
	(void)y;
	if (button == 4)
		zoom_in(pen);
	else if (button == 5)
		zoom_out(pen);
	return (1);
}

int esc_key_hook(int keycode, void *param)
{
	t_ptr	*ptr;

	ptr = (t_ptr *)param;
	if (keycode == 53)
	{
		mlx_clear_window(ptr -> mlx, ptr -> win);
		mlx_destroy_window(ptr -> mlx, ptr -> win);	
	}
	return (1);
}