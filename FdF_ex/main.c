#include <mlx.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "./libft.h"

typedef struct s_point {
	int x_pos;
	int y_pos;
	int alt;
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
			mlx_pixel_put(mlx_ptr, win_ptr, (int)x, (int)(m*(x-x1)+y1), 0x00ffffff - 0x000404*(int)grad);
		}
	}
	else
	{
		for (int x = x2; x <= x1; x++)
		{
			grad = p2.alt;
			if (p2.alt != p1.alt)
				grad += ((p1.alt - p2.alt) * (x - x2)) / (x1 - x2);
			mlx_pixel_put(mlx_ptr, win_ptr, (int)x, (int)(m*(x-x2)+y2), 0x00ffffff - 0x000404*(int)grad);
		}
	}
}
void	transform(t_point *P)
{
	int X = 0,Y = 0;

	X += (P->x_pos - origin.x_pos) * cos(3.14 / 6);
	Y -= (P->x_pos - origin.x_pos) * sin(3.14 / 6);
	X -= (P->y_pos - origin.y_pos) * cos(3.14 / 6);
	Y -= (P->y_pos - origin.y_pos) * sin(3.14 / 6);
	P->x_pos = origin.x_pos + X;
	P->y_pos = origin.y_pos + Y;
	// mlx_pixel_put(mlx_ptr, win_ptr, P->x_pos, P->y_pos, 0x00ffffff);
}
int main()
{
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 2000, 1200, "test_mlx");

	t_point axis[1000];
	int num = 0;
	int x=800, y = 100;

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			axis[num].x_pos = x + (35*i) - (35*j);
			axis[num].y_pos = y + (20*i) + (20*j);
			axis[num].alt = 0;
			num++;
		}
	}
	for(int i = 3; i < 17; i++)
	{
		if (i < 11)
		{
			axis[120 + i].alt  = 20;
			axis[140 + i].alt  = 20;
			axis[400 + i].alt  = 20;
			axis[420 + i].alt  = 20;
		}
		else
		{
			axis[300 + i].alt  = 20;
			axis[320 + i].alt  = 20;
			
		}
		axis[220 + i].alt  = 20;
		axis[240 + i].alt  = 20;
	}
	for (int i = 160; i <= 420; i+= 20)
	{
		if (i != 260 && i != 280)
		{
			axis[i + 9].alt  = 20;
			axis[i + 10].alt  = 20;
		}
		if (i > 280)
		{
			axis[i + 3].alt  = 20;
			axis[i + 4].alt  = 20;
			axis[i + 15].alt  = 20;
			axis[i + 16].alt = 20;
		}
	}
	for (int i = 0; i < num; i++)
		mlx_pixel_put(mlx_ptr, win_ptr, axis[i].x_pos, axis[i].y_pos, 0x00ff0000);
	for (int i = 0; i < num - 1; i++)
	{
		if (i % 20 != 19)
			draw_line(axis[i], axis[i+1]);
		if (i < num - 20)
			draw_line(axis[i], axis[i+20]);
	}
	printf("%x\n", 0x00ffffff);
	printf("%x\n", 0x00ffffff - (0x000200 * 2) );
	mlx_loop (mlx_ptr);


	// for (int i = -5; i < 6; i++)
	// {
	// 	mlx_pixel_put(mlx_ptr, win_ptr, axis[num/2].x_pos, axis[num/2 + i].y_pos, 0x0000ffff);
	// 	mlx_pixel_put(mlx_ptr, win_ptr, axis[num/2 + 11*i].x_pos, axis[num/2].y_pos, 0x00ffff00);
	// }
	// for (int i = -5; i < 6; i++)
	// {
	// 	transform(axis + num/2 + i);
	// 	mlx_pixel_put(mlx_ptr, win_ptr, axis[num/2 + i].x_pos, axis[num/2 + i].y_pos, 0x0000ffff);
	// 	transform(axis + num/2 + 11 + i);
	// 	mlx_pixel_put(mlx_ptr, win_ptr, axis[num/2 + 11 + i].x_pos, axis[num/2 + 11 + i].y_pos, 0x0000ffff);
	// 	transform(axis + num/2 - 11 + i);
	// 	mlx_pixel_put(mlx_ptr, win_ptr, axis[num/2 - 11 + i].x_pos, axis[num/2 - 11 + i].y_pos, 0x0000ffff);
	// 	transform(axis + num/2 + 11*i);
	// 	mlx_pixel_put(mlx_ptr, win_ptr, axis[num/2 + 11*i].x_pos, axis[num/2 + 11*i].y_pos, 0x00ffff00);
	// 	transform(axis + num/2 + 11*i + 1);
	// 	mlx_pixel_put(mlx_ptr, win_ptr, axis[num/2 + 11*i + 1].x_pos, axis[num/2 + 11*i + 1].y_pos, 0x00ffff00);
	// 	transform(axis + num/2 + 11*i - 1);
	// 	mlx_pixel_put(mlx_ptr, win_ptr, axis[num/2 + 11*i - 1].x_pos, axis[num/2 + 11*i - 1].y_pos, 0x00ffff00);
	// 	// draw_line(origin.x_pos, origin.y_pos, axis[num/2 + i].x_pos, axis[num/2 + i].y_pos);
	// }

	// mlx_pixel_put(mlx_ptr, win_ptr, axis[num/2 - 1].x_pos, axis[num/2 - 1].y_pos, 0x00ffffff);
	// mlx_pixel_put(mlx_ptr, win_ptr, axis[num/2].x_pos, axis[num/2].y_pos, 0x000000ff);

	// mlx_string_put(mlx_ptr, win_ptr, 200, 0, 0xaaaaaa, "hello");
	// int height, width;
	// void *img_ptr = mlx_xpm_file_to_image(mlx_ptr, "./sample_640×426.xpm", &height, &width);
	// mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 200, 200);

}