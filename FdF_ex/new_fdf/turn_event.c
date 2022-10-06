#include "fdf.h"

void	turn_right(t_point **coord, t_point **o_map, t_img *img)
{
	turn_x(coord, o_map, img, theta);
	turn_y(coord, o_map, img, 0);
}

void	turn_left(t_point **coord, t_point **o_map, t_img *img)
{
	turn_x(coord, o_map, img, -theta);
	turn_y(coord, o_map, img, 0);
}

void	turn_up(t_point **coord, t_point **o_map, t_img *img)
{
	turn_x(coord, o_map, img, 0);
	turn_y(coord, o_map, img, theta);
}

void	turn_down(t_point **coord, t_point **o_map, t_img *img)
{
	turn_x(coord, o_map, img, 0);
	turn_y(coord, o_map, img, -theta);
}
