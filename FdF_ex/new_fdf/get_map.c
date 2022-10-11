/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:32:12 by woojeong          #+#    #+#             */
/*   Updated: 2022/10/11 15:40:07 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./fdf.h"

t_point	**get_coordinate(char *map, t_img *img)
{
	t_point	**coord;
	t_list	*line_list;
	int		fd;

	fd = open_map(map);
	if (fd == 0)
		return (NULL);
	init_img(img);
	line_list = map_to_list(fd, img);
	close(fd);
	if (!line_list)
		return (NULL);
	coord = list_to_coord(line_list, img);
	ft_lstclear(&line_list, del_free);
	return (coord);
}

t_list	*map_to_list(int fd, t_img *img)
{
	t_list	*line_list;
	t_list	*head;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	line_list = ft_lstnew(line);
	head = line_list;
	while (line_list)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line_list -> next = ft_lstnew(line);
		line_list = line_list -> next;
	}
	if (!line_list || line < 0)
	{
		ft_lstclear(&head, del_free);
		return (NULL);
	}
	return (head);
}

t_point	**list_to_coord(t_list *line_list, t_img *img)
{
	t_point	**coord;
	int		y;

	img -> y_size = ft_lstsize(line_list);
	coord = (t_point **)malloc(sizeof(t_point *) * (img -> y_size));
	if (!coord)
		return (NULL);
	y = 0;
	while (y < img -> y_size)
	{
		if (!line_to_coord(line_list -> content, coord, y, img))
			return (free_point_arr(coord, y));
		y++;
		line_list = line_list -> next;
	}
	return (coord);
}

int	line_to_coord(char *line, t_point **coord, int y, t_img *img)
{
	char	**spl;
	int		len;
	int		x;

	spl = ft_split(line, ' ');
	if (!spl)
		return (0);
	if (!check_len(spl, &len, img))
		return (0);
	coord[y] = (t_point *)malloc(sizeof(t_point) * (len));
	if (!coord[y])
		return (free_split(spl));
	x = 0;
	while (x < len)
	{
		coord[y][x].alt = ft_atoi(spl[x]);
		if (img -> max_alt < fabs(coord[y][x].alt))
			img -> max_alt = fabs(coord[y][x].alt);
		x++;
	}
	free_split(spl);
	return (1);
}

t_point	**save_original_map(t_point **coord, t_img *img)
{
	t_point	**o_map;
	int		y;
	int		x;

	o_map = (t_point **)malloc(sizeof(t_point *) * img -> y_size);
	if (!o_map)
		return (NULL);
	y = 0;
	while (y < img -> y_size)
	{
		o_map[y] = (t_point *)malloc(sizeof(t_point) * img -> x_size);
		if (!o_map[y])
			return (free_point_arr(o_map, y));
		x = 0;
		while (x < img -> x_size)
		{
			o_map[y][x].x_pos = coord[y][x].x_pos;
			o_map[y][x].y_pos = coord[y][x].y_pos;
			o_map[y][x].alt = coord[y][x].alt;
			x++;
		}
		y++;
	}
	return (o_map);
}
