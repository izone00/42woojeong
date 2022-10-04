#include "fdf.h"

void	turn_x(t_point **axis, t_point **o_map, t_img *img, double angle)
{
	static double	pre_angle;
	int	x;
	int	y;

	pre_angle += angle;
	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			axis[y][x].x_pos -= (img -> move)[x_move];
			axis[y][x].y_pos -= (img -> move)[y_move];
			axis[y][x].x_pos = o_map[y][x].x_pos * cos(pre_angle) - o_map[y][x].y_pos * sin(pre_angle);
			axis[y][x].y_pos = o_map[y][x].x_pos * sin(pre_angle) + o_map[y][x].y_pos * cos(pre_angle);
			// ft_printf("[%d, %d] ", (int)axis[y][x].x_pos, (int)axis[y][x].y_pos);
			x++;
		}
		// ft_printf("\n");
		y++;
	}
}

void	turn_y(t_point **axis, t_point **o_map, t_img *img, double angle)
{
	static double	pre_angle;
	int	x;
	int	y;
	double	pre_x;
	double	pre_y;

	y = 0;
	pre_angle += angle;
	// ft_printf("%d", (int)(cos(pre_angle) * 100));
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			axis[y][x].y_pos = (axis[y][x].y_pos) * cos(pre_angle);
			axis[y][x].y_pos += axis[y][x].alt * (sin(pre_angle));
			axis[y][x].x_pos += (img -> move)[x_move];
			axis[y][x].y_pos += (img -> move)[y_move];
			// printf("[%.1f, %.1f]\n ", axis[y][x].x_pos, axis[y][x].y_pos);
			x++;
		}
		// printf("\n");
		y++;
	}
	
}