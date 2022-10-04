#include "fdf.h"

void	turn_right(t_point **axis, t_point **o_map, t_img *img)
{
	turn_x(axis, o_map, img, theta);
	turn_y(axis, o_map, img, 0);
}

void	turn_left(t_point **axis, t_point **o_map, t_img *img)
{
	turn_x(axis, o_map, img, -theta);
	turn_y(axis, o_map, img, 0);
}

void	turn_up(t_point **axis, t_point **o_map, t_img *img)
{
	turn_x(axis, o_map, img, 0);
	turn_y(axis, o_map, img, -theta);
}

void	turn_down(t_point **axis, t_point **o_map, t_img *img)
{
	turn_x(axis, o_map, img, 0);
	turn_y(axis, o_map, img, +theta);
}
