#include "./fdf.h"

int	draw_img(t_point **coord, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			if (x > 0)
				draw_line(&(coord[y][x - 1]), &(coord[y][x]), img);
			if (y < img -> y_size - 1)
				draw_line(&(coord[y][x]), &(coord[y + 1][x]), img);
			x++;
		}
		y++;
	}
	return (1);
}

void	draw_line(t_point *p1, t_point *p2, t_img *img)
{
	if (check_point(p1, p2, img))
	{
		if (p1 -> x_pos < p2 -> x_pos)
			draw_by_x(p1, p2, img);
		else if (p1 -> x_pos > p2 -> x_pos)
			draw_by_x(p2, p1, img);
		if (p1 -> y_pos < p2 -> y_pos)
			draw_by_y(p1, p2, img);
		else if (p1 -> y_pos > p2 -> y_pos)
			draw_by_y(p2, p1, img);
	}
}

void	draw_by_x(t_point *p1, t_point *p2, t_img *img)
{
	double	m;
	double	x;
	double	y;
	double	alt_m;
	int		grad;

	m = ((p2 -> y_pos) - (p1 -> y_pos)) / ((p2 -> x_pos) - (p1 -> x_pos));
	x = (p1 -> x_pos);
	y = m * (x - (p1 -> x_pos)) + (p1 -> y_pos);
	alt_m = ((p2 -> alt) - (p1 -> alt)) / ((p2 -> x_pos) - (p1 -> x_pos));
	while (x <= p2 -> x_pos)
	{
		grad = fabs(255 * ((p1 -> alt + alt_m * (x - p1 -> x_pos))\
						 / img -> max_alt));
		grad *= 0x00000101;
		color_pixel(x, y, 0x00ff0000 + grad, img);
		y += m;
		x++;
	}
}
void	draw_by_y(t_point *p1, t_point *p2, t_img *img)
{
	double	m;
	double	x;
	double	y;
	double	alt_m;
	int		grad;

	m = (p2 -> x_pos - p1 -> x_pos) / (p2 -> y_pos - p1 -> y_pos);
	y = p1 -> y_pos;
	x = m * (y - p1 -> y_pos) + p1 -> x_pos;
	alt_m = ((p2 -> alt) - (p1 -> alt)) / ((p2 -> y_pos) - (p1 -> y_pos));
	while (y <= p2 -> y_pos)
	{
		grad = fabs(255 * ((p1 -> alt + alt_m * (y - p1 -> y_pos))\
							 / img -> max_alt));
		grad *= 0x00000101;
		color_pixel(x, y, 0x00ff0000 + grad, img);
		x += m;
		y++;
	}
}
