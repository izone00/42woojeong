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
int	rotate_key_hook(int keycode, void *pen);
int	mouse_hook(int button, int x,int y, void *param);
//temp
#define end (-1)
#define trans 40
#define theta 3.14 / 12

enum e_move {
	y_move = 0,
	x_move = 1,
};

typedef struct s_point {
	double x_pos;
	double y_pos;
	double alt;
} t_point;
typedef struct s_ptr {
	void	*mlx;
	void	*win;
	void	*img;
} t_ptr;
typedef struct s_img {
	int	x_size;
	int	y_size;
	int x_origin;
	int	y_origin;
	int	h_scale;//
	int w_scale;//
	double	scale;
	double	adjust;
	double	max_alt;
	char	*addr;
	char	*o_addr;
	int		move[2];
	int	bits_per_pixel;
	int	size_line;
	int	endian;
} t_img;
						//temp
						typedef struct s_pen {
							t_ptr	*ptr;
							t_img	*img;
							t_point	**axis;
							t_point	**o_map;
						} t_pen;
//get_map
t_point	**get_map_axis(char *map, t_img *img);
t_list	*get_axis(int fd, t_img *img);
void	del_free(void *ptr);
int	open_map(char *map);
int	line_to_axis(char *line, t_point **axis, int y, t_img *img);
t_point	**save_original_map(t_point **axis, t_img *img);
t_point	**list_to_arr(t_list *line_list, t_img *img);
//draw_img
int	draw_img(t_point **axis, t_img *img);
void	draw_line(t_point *p1, t_point *p2, t_img *img);
void	color_pixel(int x, int y, int color, t_img *img);
void	get_img_origin(t_img *img);
//get_img_size
int	get_img_size(t_point **axis, t_img *img);
void	change_img_scale(t_point **axis, t_img *img);
//turn
void	turn_x(t_point **axis, t_point **o_map, t_img *img, double angle);
void	turn_y(t_point **axis, t_point **o_map, t_img *img, double angle);
//event
int esc_key_hook(int keycode, void *param);
//turn_event
void	turn_right(t_point **axis, t_point **o_map, t_img *img);
void	turn_left(t_point **axis, t_point **o_map, t_img *img);
void	turn_up(t_point **axis, t_point **o_map, t_img *img);
void	turn_down(t_point **axis, t_point **o_map, t_img *img);
//translate
void	trans_up(t_point **axis, t_point **o_map, t_img *img);
void	trans_down(t_point **axis, t_point **o_map, t_img *img);
void	trans_right(t_point **axis, t_point **o_map, t_img *img);
void	trans_left(t_point **axis, t_point **o_map, t_img *img);
//util
void	free_point_arr(t_point **arr, int len);
void	free_split(char **arr);
#endif