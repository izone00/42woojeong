#include "./fdf.h"

int	draw_img(t_point **axis, t_img *img)
{
	int	x;
	int	y;
	for	(int i = 0;i < img -> width - 1;i++)
	{
		*(int *)(img -> addr) = 0x0000ffff;
		*(int *)((img -> addr) + ((int)(img -> height) - 1) * (img -> size_line)) = 0x0000ffff;
		img -> addr += 4;
	}
	y = 0;
	while (y < img -> y_size - 1)
	{
		x = img -> x_size - 1;
		while (x >= 1)
		{
			draw_line(axis[y][x - 1], axis[y][x], img);
			x--;
		}
		x = img -> x_size - 1;
		while (x >= 0)
		{
			draw_line(axis[y][x], axis[y + 1][x], img);
			x--;
		}
		y++;
	}
	x = img -> x_size - 1;
	while (x >= 1)
	{
		draw_line(axis[img -> y_size - 1][x - 1], axis[img -> y_size - 1][x], img);
		x--;
	}
	return (1);
}

void	draw_line(t_point p1, t_point p2, t_img *img)
{
	double	x;
	double	y;
	double	m;

	m = ((p2.y_pos - p2.alt) - (p1.y_pos - p1.alt)) / (p2.x_pos - p1.x_pos);
	x = p1.x_pos;
	y = p1.y_pos - p1.alt + img -> adjust;
	while (x < p2.x_pos)
	{
		color_pixel((int)x, (int)y, 0x00ffffff, img);
		y += m;
		x++;
	}
	if (p1.y_pos - p1.alt < p2.y_pos - p2.alt)
	{
		y = p1.y_pos - p1.alt + img -> adjust;
		x = p1.x_pos;
		while (y < p2.y_pos - p2.alt + img -> adjust)
		{
			color_pixel((int)x, (int)y, 0x00ffffff, img);
			x += (1/m);
			y++;
		}
	}
	else
	{
		y = p2.y_pos - p2.alt + img -> adjust;
		x = p2.x_pos;
		while (y < p1.y_pos - p1.alt + img -> adjust)
		{
			color_pixel((int)x, (int)y, 0x00ffffff, img);
			x += (1/m);
			y++;
		}
	}
}
void	color_pixel(int x, int y, int color, t_img *img)
{
	char	*img_addr;

	img_addr = 	img -> addr;
	img_addr += y * (img -> size_line);
	img_addr += x * ((img -> bits_per_pixel) / 8);
	*(int *)img_addr = color;
}
int	get_img_size(t_point **axis, t_img *img)
{
	double	top;
	int		x;
	int		y;
	int		x_len;

	x_len = 0;
	top = 0;
	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (axis[y][x].x_pos >= 0)
		{
			if (top > axis[y][x].y_pos - axis[y][x].alt)
				top = axis[y][x].y_pos - axis[y][x].alt;
			x++;
		}
		if (x_len == 0)
			x_len = x;
		else if (x_len != x)
		{
			
			write(1, "wrong map", 9);
			return (0);
		}
		y++;
	}
	img -> x_size = x_len;
	img -> height = axis[(img -> y_size) - 1][0].y_pos - top + 1;
	img -> width = axis[img -> y_size - 1][img -> x_size - 1].x_pos - axis[0][0].x_pos;
	img -> adjust = top * (-1);
	return (1);
}
