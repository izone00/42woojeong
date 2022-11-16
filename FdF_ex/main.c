#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

#include "./libft.h"

int x=100, y = 800;

typedef struct s_point {
	double x_pos;
	double y_pos;
	double alt;
} t_point;

void	*mlx_ptr;
void	*win_ptr;
t_point origin;

void	draw_line(t_point p1, t_point p2)
{
	double	m;
	double 	grad;
	int color = 0x00ffffff;			

	double x1 = p1.x_pos;
	double x2 = p2.x_pos;
	p1.alt *= 1.5;
	p2.alt *= 1.5;
	double y1 = p1.y_pos - p1.alt;
	double y2 = p2.y_pos - p2.alt;
	
	m = (y1-y2) /(x1-x2);
	if (x1 == x2)
	{
		for (int y = y1; y <= y2; y++)
			mlx_pixel_put(mlx_ptr, win_ptr, (int)x1, (int)y, 0x00ffffff);
	}
	else if (x1 < x2)
	{
		for (int x = x1; x <= x2; x++)
		{
			grad = p1.alt;
			if (p2.alt != p1.alt)
				grad += ((p2.alt - p1.alt) * (x - x1)) / (x2 - x1);
			if (grad < 0)
				grad *= -1;
			mlx_pixel_put(mlx_ptr, win_ptr, (int)x, (int)(m*(x-x1)+y1), 0x00ffffff);
			if (m > 0)
			{
				for (int i = 0; i < m; i++)
					mlx_pixel_put(mlx_ptr, win_ptr, (int)x, (int)(m*(x-x2)+y2 + i), 0x00ffffff);
			}
			else
			{
				for (int i = 0; i > m; i--)
					mlx_pixel_put(mlx_ptr, win_ptr, (int)x, (int)(m*(x-x2)+y2 + i), 0x00ffffff);
			}
		}
	}
	else
	{
		for (int x = x2; x <= x1; x++)
		{
			grad = p2.alt;
			if (p2.alt != p1.alt)
				grad += ((p1.alt - p2.alt) * (x - x2)) / (x1 - x2);
			if (grad < 0)
				grad *= -1;
			mlx_pixel_put(mlx_ptr, win_ptr, (int)x, (int)(m*(x-x2)+y2), 0x00ffffff);
			if (m > 0)
			{
				for (int i = 0; i < m; i++)
					mlx_pixel_put(mlx_ptr, win_ptr, (int)x, (int)(m*(x-x2)+y2 + i), 0x00ffffff);
			}
			else
			{
				for (int i = 0; i > m; i--)
					mlx_pixel_put(mlx_ptr, win_ptr, (int)x, (int)(m*(x-x2)+y2 + i), 0x00ffffff);
			}
		}
	}
}

int	get_map_info(int *x_size, int *y_size, t_point *coord, char *file)
{
	int num = 0;
	int fd = open(ft_strjoin("./", file), O_RDONLY);

	for (int j = 0; ; j++)
	{
		char *line = get_next_line(fd);
		if (!line)
			break ;
		char **spl = ft_split(line, ' ');
		for (int i = 0; spl[i] && spl[i][0] != '\n'; i++)
		{
			coord[num].x_pos = x + (5*sqrt(3)*j) + (5*sqrt(3)*i);
			coord[num].y_pos = y + (5*j) - (5*i);
			// coord[num].alt = ft_atoi(spl[i])*5;
			num++;
			*x_size = i + 1;
		}
		*y_size = j + 1;
	}
	return (num);
}
int key_hook(int keycode, void *param)
{
	if (keycode == 53)
	{
		mlx_clear_window(mlx_ptr, win_ptr);
		mlx_destroy_window(mlx_ptr, win_ptr);
		exit(0);
	}
	return (1);
}

int main(int argc, char *argv[])
{
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 2000, 1200, "test_mlx");

	t_point *coord;
	coord = malloc(sizeof(t_point) * 100000000);
	int num = 0;
	
	int x_size = 0, y_size = 0;
	num = get_map_info(&x_size, &y_size, coord, argv[1]);
	for (int i = 0; i < num - 1; i++)
	{
		if (i % x_size != x_size - 1)
			draw_line(coord[i], coord[i+1]);
		if (i < num - x_size)
			draw_line(coord[i], coord[i+x_size]);
	}
	void *param;
	mlx_key_hook(win_ptr, key_hook, param);
	mlx_loop (mlx_ptr);
}

	// void	*img_ptr = mlx_new_image(mlx_ptr, 200, 200);
	// int bits_per_pixel, size_line, endian;
	// char	*img_addr = mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);
	// for (int i = 0; i < 10; i++)
	// {
	// 	*(img_addr) = 0xff;
	// 	*(img_addr+1) = 0xff;
	// 	*(img_addr+2) = 0xff;
	// 	*(img_addr+3) = 0x00;
	// 	img_addr += size_line;
	// }
	// mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 500, 500);