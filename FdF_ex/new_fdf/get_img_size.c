#include "fdf.h"

int	get_img_size(t_point **axis, t_img *img)
{
	int		x;
	int		y;
	double	multiple;

	img -> scale = sqrt(pow(2 * (img -> max_alt), 2) \
	+ pow(sqrt((img -> x_size) * (img -> x_size) + (img -> y_size) * (img -> y_size)), 2)) + 20;
	multiple = 1;
	while (img -> scale * multiple < 1000)
		multiple += 0.2;
	img -> scale *= multiple;
	img -> x_origin = (img -> x_size - 1) / 2;
	img -> y_origin = (img -> y_size - 1) / 2;
	// printf("[%f]\n", img -> scale);
	y = 0;
	while (y < img -> y_size)
	{
		x = 0;
		while (x < img -> x_size)
		{
			axis[y][x].x_pos = (x - img -> x_origin) * multiple;
			axis[y][x].y_pos = (y - img -> y_origin) * multiple;
			axis[y][x].alt *= multiple;
			// printf("[%.1f, %.1f] ", axis[y][x].x_pos, axis[y][x].y_pos);
			x++;
		}
		// printf("\n");
		y++;
	}
	(img -> max_alt) *= multiple;
	return (1);
}
