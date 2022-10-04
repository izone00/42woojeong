#include "fdf.h"

void	trans_up(t_point **axis, t_point **o_map, t_img *img)
{
	int		x;
	int		y;

	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			axis[y][x].y_pos -= trans;
			x++;
		}
		y++;
	}
	(img -> move)[y_move] -= trans;
}

void	trans_down(t_point **axis, t_point **o_map, t_img *img)
{
	int		x;
	int		y;

	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			axis[y][x].y_pos += trans;
			x++;
		}
		y++;
	}
	(img -> move)[y_move] += trans;
}

void	trans_right(t_point **axis, t_point **o_map, t_img *img)
{
	int		x;
	int		y;

	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			axis[y][x].x_pos += trans;
			x++;
		}
		y++;
	}
	(img -> move)[x_move] += trans;
}

void	trans_left(t_point **axis, t_point **o_map, t_img *img)
{
	int		x;
	int		y;

	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			axis[y][x].x_pos -= trans;
			x++;
		}
		y++;
	}
	(img -> move)[x_move] -= trans;
}