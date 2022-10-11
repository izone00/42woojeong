/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:31:48 by woojeong          #+#    #+#             */
/*   Updated: 2022/10/11 15:32:45 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
int	rotate_key_hook(int keycode, void *param);
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
	int		map_err;//get_map
	int		x_size;//get_map
	int		y_size;//get_map
	double	max_alt;//get_map
	double	scale;//get_img_scale
	char	*addr;//main
	int		bits_per_pixel;//main
	int		size_line;//main
	int		endian;//main
	char	*center;//get_img_center_addr
	int		move[2];//turn
} t_img;
typedef struct s_param {
	t_ptr	*ptr;
	t_img	*img;
	t_point	**coord;
	t_point	**o_map;
} t_param;
//get_map
t_point	**get_coordinate(char *map, t_img *img);
t_list	*map_to_list(int fd, t_img *img);
t_point	**list_to_coord(t_list *line_list, t_img *img);
int	line_to_coord(char *line, t_point **coord, int y, t_img *img);
t_point	**save_original_map(t_point **coord, t_img *img);
//get_map_utils
int		open_map(char *map);
int		free_split(char **arr);
void	del_free(void *ptr);
void	init_img(t_img *img);
int		check_len(char **spl, int *len, t_img *img);
//draw_img
int	draw_img(t_point **coord, t_img *img);
void	draw_line(t_point *p1, t_point *p2, t_img *img);
void	draw_by_x(t_point *p1, t_point *p2, t_img *img);
void	draw_by_y(t_point *p1, t_point *p2, t_img *img);
//draw_img_utils
int	check_point(t_point *p1, t_point *p2, t_img *img);
void	color_pixel(int x, int y, int color, t_img *img);
void	get_img_center_addr(t_img *img);
//get_img_scale
int		get_img_scale(t_point **coord, t_img *img);
void	change_img_scale(double multiple, t_point **coord, t_img *img);
//turn
void	turn_x(t_point **coord, t_point **o_map, t_img *img, double angle);
void	turn_y(t_point **coord, t_point **o_map, t_img *img, double angle);
//event
int	key_hook(int keycode, void *param);
int	mouse_hook(int button, int x,int y, void *param);
//turn_event
void	turn_right(t_point **coord, t_point **o_map, t_img *img);
void	turn_left(t_point **coord, t_point **o_map, t_img *img);
void	turn_up(t_point **coord, t_point **o_map, t_img *img);
void	turn_down(t_point **coord, t_point **o_map, t_img *img);
//translate
void	trans_up(t_point **coord, t_point **o_map, t_img *img);
void	trans_down(t_point **coord, t_point **o_map, t_img *img);
void	trans_right(t_point **coord, t_point **o_map, t_img *img);
void	trans_left(t_point **coord, t_point **o_map, t_img *img);
//zoom
void	zoom_in(t_point **coord, t_point **o_map, t_img *img);
void	zoom_out(t_point **coord, t_point **o_map, t_img *img);
//util
t_point	**free_point_arr(t_point **arr, int len);
#endif