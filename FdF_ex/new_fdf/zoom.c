#include "fdf.h"

void	zoom_in(t_point **coord, t_point **o_map, t_img *img)
{
	int		x;
	int		y;
	
	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			coord[y][x].x_pos *= 1.2;
			coord[y][x].y_pos *= 1.2;
			coord[y][x].alt *= 1.2;
			o_map[y][x].x_pos *= 1.2;
			o_map[y][x].y_pos *= 1.2;
			o_map[y][x].alt *= 1.2;
			x++;
		}
		y++;
	}
	(img -> max_alt) *= 1.2;
	(img -> move)[y_move] *= 1.2;
	(img -> move)[x_move] *= 1.2;
}

void	zoom_out(t_point **coord, t_point **o_map, t_img *img)
{
	int		x;
	int		y;

	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			coord[y][x].x_pos /= 1.2;
			coord[y][x].y_pos /= 1.2;
			coord[y][x].alt /= 1.2;
			o_map[y][x].x_pos /= 1.2;
			o_map[y][x].y_pos /= 1.2;
			o_map[y][x].alt /= 1.2;
			x++;
		}
		y++;
	}
	(img -> max_alt) /= 1.2;
	(img -> move)[y_move] /= 1.2;
	(img -> move)[x_move] /= 1.2;
}