#ifndef FDF_H
# define FDF_H

#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "./libft.h"

//temp
#include <stdio.h>
int	ft_printf(char *str, ...);
//temp
#define end (-1)

typedef struct s_point {
	double x_pos;
	double y_pos;
	double alt;
} t_point;

typedef struct s_img {
	int	x_size;//?????
	int	y_size;
	double	height;
	double	width;
	double	adjust;
	char	*addr;
	int	bits_per_pixel;
	int	size_line;
	int	endian;
} t_img;

//get_map
t_point	**get_map_axis(char *map, t_img *img);
t_list	*get_axis(int fd, t_img *img);
void	del_free(void *ptr);
int	open_map(char *map);
int	line_to_axis(char *line, t_point **axis, int y);
t_point	**list_to_arr(t_list *line_list, t_img *img);
//draw_img
int	get_img_size(t_point **axis, t_img *img);
int	draw_img(t_point **axis, t_img *img);
void	draw_line(t_point p1, t_point p2, t_img *img);
void	color_pixel(int x, int y, int color, t_img *img);
//util
void	free_point_arr(t_point **arr, int len);
void	free_split(char **arr);
#endif