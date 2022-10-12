/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:31:48 by woojeong          #+#    #+#             */
/*   Updated: 2022/10/12 16:30:24 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "./libft.h"

enum e_move {
	y_move = 0,
	x_move = 1,
};

typedef struct s_point {
	double	x_pos;
	double	y_pos;
	double	alt;
}	t_point;
typedef struct s_ptr {
	void	*mlx;
	void	*win;
	void	*img;
}	t_ptr;
typedef struct s_img {
	int		map_err;
	int		x_size;
	int		y_size;
	double	max_alt;
	double	scale;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	char	*center;
	int		move[2];
}	t_img;
typedef struct s_param {
	t_ptr	*ptr;
	t_img	*img;
	t_point	**coord;
	t_point	**o_map;
}	t_param;

t_point	**get_coordinate(char *map, t_img *img);
t_list	*map_to_list(int fd, t_img *img);
t_point	**list_to_coord(t_list *line_list, t_img *img);
int		line_to_coord(char *line, t_point **coord, int y, t_img *img);
t_point	**save_original_map(t_point **coord, t_img *img);
int		open_map(char *map);
int		free_split(char **arr);
void	del_free(void *ptr);
void	init_img(t_img *img);
int		check_len(char **spl, int *len, t_img *img);
int		draw_img(t_point **coord, t_img *img);
void	draw_line(t_point *p1, t_point *p2, t_img *img);
void	draw_by_x(t_point *p1, t_point *p2, t_img *img);
void	draw_by_y(t_point *p1, t_point *p2, t_img *img);
int		check_point(t_point *p1, t_point *p2, t_img *img);
void	color_pixel(int x, int y, int color, t_img *img);
void	get_img_center_addr(t_img *img);
int		get_img_scale(t_point **coord, t_img *img);
void	change_img_scale(double multiple, t_point **coord, t_img *img);
void	turn_x(t_point **coord, t_point **o_map, t_img *img, double angle);
void	turn_y(t_point **coord, t_point **o_map, t_img *img, double angle);
int		key_hook(int keycode, void *param);
int		mouse_hook(int button, int x, int y, void *param);
void	turn_right(t_point **coord, t_point **o_map, t_img *img);
void	turn_left(t_point **coord, t_point **o_map, t_img *img);
void	turn_up(t_point **coord, t_point **o_map, t_img *img);
void	turn_down(t_point **coord, t_point **o_map, t_img *img);
void	trans_up(t_point **coord, t_point **o_map, t_img *img);
void	trans_down(t_point **coord, t_point **o_map, t_img *img);
void	trans_right(t_point **coord, t_point **o_map, t_img *img);
void	trans_left(t_point **coord, t_point **o_map, t_img *img);
void	zoom_in(t_point **coord, t_point **o_map, t_img *img);
void	zoom_out(t_point **coord, t_point **o_map, t_img *img);
t_point	**free_point_arr(t_point **arr, int len);
void	argc_err(void);
void	mlx_err(void);
void	wrong_map(void);
void	coord_err(void);
void	win_err(t_point **coord, t_point **o_map, t_img *img);
#endif