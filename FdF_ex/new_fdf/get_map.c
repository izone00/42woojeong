#include "./fdf.h"
static void	init_img(t_img *img);

t_point	**get_map_axis(char *map, t_img *img)
{
	t_point **axis_arr;
	t_list	*line_list;
	int 	fd;

	fd = open_map(map); // open
	if (fd == 0)
		return (NULL);
	init_img(img);
	line_list = get_axis(fd, img); //malloc
	close(fd);
	if (!line_list)
		return (NULL);
	axis_arr = list_to_arr(line_list, img); //malloc
	ft_lstclear(&line_list, del_free);
	return (axis_arr);
}
int	line_to_axis(char *line, t_point **axis, int y, t_img *img)
{
	char	**spl;
	int		len;
	int		x;

	spl = ft_split(line, ' ');
	if (!spl)
		return (0);
	len = 0; 
	while (spl[len] && spl[len][0] != '\n')
		len++;
	if (img -> x_size == 0)
		img -> x_size = len;
	else if (img -> x_size != len)
	{
		write(2, "wrong map\n", 10);
		free_split(spl);
		return (0);
	}
	axis[y] = (t_point *)malloc(sizeof(t_point) * (len));
	if (!axis[y])
	{
		perror("zsh");
		free_split(spl);
		return (0);
	}
	x = 0;
	while (x < len)
	{
		axis[y][x].alt = ft_atoi(spl[x]);
		if (img -> max_alt < fabs(axis[y][x].alt))
			img -> max_alt = fabs(axis[y][x].alt);
		x++;
	}
	free_split(spl);
	return (1);
}
t_point	**list_to_arr(t_list *line_list, t_img *img)
{
	t_point **axis_arr;
	int		y;

	img -> y_size = ft_lstsize(line_list);
	axis_arr = (t_point **)malloc(sizeof(t_point *) * (img -> y_size));
	if (!axis_arr)
		return (NULL);
	y = 0;
	while (y < img -> y_size)
	{
		if (!line_to_axis(line_list -> content, axis_arr, y, img))
		{
			free_point_arr(axis_arr, y);
			return (NULL);
		}
		y++;
		line_list = line_list -> next;
	}
	return (axis_arr);
}
t_list	*get_axis(int fd, t_img *img)
{
	t_list	*line_list;
	t_list	*head;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	line_list = ft_lstnew(line);
	head = line_list;
	while(line_list)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		line_list -> next = ft_lstnew(line);
		line_list = line_list -> next;
	}
	if (!line_list)
	{
		ft_lstclear(&head, del_free);//왜 주소를 전달하는지 모르겠다.
		return (NULL);
	}
	return (head);
}

int	open_map(char *map)
{
	char	*map_path;
	int		fd;

	map_path = ft_strjoin("./", map);
	if (!map_path)
		return (0);
	fd = open(map_path, O_RDONLY);
	free(map_path);
	if (fd < 0)
		return (0);
	return (fd);
}

t_point	**save_original_map(t_point **axis, t_img *img)
{
	t_point	**o_map;
	int	y;
	int	x;

	o_map = (t_point **)malloc(sizeof(t_point *) * img -> y_size);
	if (!o_map)
		return (NULL);
	y = 0;
	while (y < img -> y_size)
	{
		o_map[y] = (t_point *)malloc(sizeof(t_point) * img -> x_size);
		// if (!o_map[y])
		// {}//err
		x = 0;
		while (x < img -> x_size)
		{
			o_map[y][x].x_pos = axis[y][x].x_pos;
			o_map[y][x].y_pos = axis[y][x].y_pos;
			o_map[y][x].alt = axis[y][x].alt;
			x++;
		}
		y++;
	}
	return (o_map);
}
static void	init_img(t_img *img)
{
	img -> x_size = 0;
	img -> y_size = 0;
	img -> max_alt = 0;
	(img -> move)[0] = 0;
	(img -> move)[1] = 0;
}

void	del_free(void *ptr)
{
	free((char *)ptr);
}