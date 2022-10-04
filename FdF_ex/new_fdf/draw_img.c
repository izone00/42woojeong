#include "./fdf.h"

int	draw_img(t_point **axis, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < img -> y_size - 1)
	{
		x = img -> x_size - 1;
		while (x >= 1)
		{
			draw_line(&(axis[y][x - 1]), &(axis[y][x]), img);
			x--;
		}
		x = img -> x_size - 1;
		while (x >= 0)
		{
			draw_line(&(axis[y][x]), &(axis[y + 1][x]), img);
			x--;
		}
		y++;
	}
	x = img -> x_size - 1;
	while (x >= 1)
	{
		draw_line(&(axis[img -> y_size - 1][x - 1]), &(axis[img -> y_size - 1][x]), img);
		x--;
	}
	return (1);
}

int	get_color(int alt_p1, int alt_m, int max_alt, double dx)
{
	// ft_putnbr_fd(255 * ((alt_p1 + alt_m * dx) / max_alt), 1);
	// ft_putchar_fd('\n', 1);
	return (255 * ((alt_p1 + alt_m * dx) / max_alt));
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
		grad = get_color(p1 -> alt, alt_m, img -> max_alt, x - (p1 -> x_pos));
		// if (grad && alt_m)
		// 	ft_printf("[%d %d %d %d :%d]\n", (int)(p1 -> alt), (int)(alt_m), (int)(img -> max_alt), (int)(x - (p1 -> x_pos)), grad);
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
		grad = get_color(p1 -> alt, alt_m, img -> max_alt, y - (p1 -> y_pos));
		grad *= 0x00000101;
		color_pixel(x, y, 0x00ff0000 + grad, img);
		x += m;
		y++;
	}
}

int	check_point(t_point *p1, t_point *p2, t_img *img)
{
	if (p1 -> x_pos < -((img -> scale / 2) - 10) || p1 -> x_pos > ((img -> scale / 2) - 10))
		return (0);
	else if (p1 -> y_pos < -((img -> scale / 2) - 10) || p1 -> y_pos > ((img -> scale / 2) - 10))
		return (0);
	else if (p2 -> x_pos < -((img -> scale / 2) - 10) || p2 -> x_pos > ((img -> scale / 2) - 10))
		return (0);
	else if (p2 -> y_pos < -((img -> scale / 2) - 10) || p2 -> y_pos > ((img -> scale / 2) - 10))
		return (0);
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
void	color_pixel(int x, int y, int color, t_img *img)
{
	char	*img_addr;

	img_addr = 	img -> o_addr;
	img_addr += y * (img -> size_line);
	img_addr += x * ((img -> bits_per_pixel) / 8);
	if (*(int *)img_addr < color)
		*(int *)img_addr = color;
}

void	get_img_origin(t_img *img)
{
	img -> o_addr = img -> addr;
	img -> o_addr += (int)(img -> scale / 2) * (img -> size_line);
	img -> o_addr += (int)(img -> scale / 2) * ((img -> bits_per_pixel) / 8);
}

void	pre_draw_line(t_point p1, t_point p2, t_img *img)
{
	double	x;
	double	y;
	double	m;

	m = ((p2.y_pos - p2.alt) - (p1.y_pos - p1.alt)) / (p2.x_pos - p1.x_pos);
	x = p1.x_pos;
	y = p1.y_pos - p1.alt + img -> adjust;
	while (x <= p2.x_pos)
	{
		y += m;
		x++;
	}
	if (p1.y_pos - p1.alt <= p2.y_pos - p2.alt)
	{
		y = p2.y_pos - p2.alt + img -> adjust;
		x = p2.x_pos;
		while (y > p1.y_pos - p1.alt + img -> adjust)
		{
			x -= (1/m);
			y--;
		}
	}
	else
	{
		y = p1.y_pos - p1.alt + img -> adjust;
		x = p1.x_pos;
		while (y >= p2.y_pos - p2.alt + img -> adjust)
		{
			x -= (1/m);
			y--;
		}
	}
}
