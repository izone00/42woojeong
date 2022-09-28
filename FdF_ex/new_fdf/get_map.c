#include "./fdf.h"

void	print(void *str)
{
	ft_putstr_fd((char *)str, 1);
}
t_point	**get_map_axis(char *map, t_img *img)
{
	t_point **axis_arr;
	t_list	*line_list;
	int 	fd;

	fd = open_map(map); // open
	if (fd == 0)
		return (NULL);
	line_list = get_axis(fd, img); //malloc
	//ft_lstiter(line_list, print);
	close(fd);
	if (!line_list)
		return (NULL);
	axis_arr = list_to_arr(line_list, img); //malloc
	ft_lstclear(&line_list, del_free);
	return (axis_arr);
}
int	line_to_axis(char *line, t_point **axis, int y)
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
	axis[y] = (t_point *)malloc(sizeof(t_point) * (len + 1));
	if (!axis[y])
	{
		free_split(spl);
		return (0);
	}
	x = 0;
	while (x < len)
	{
		axis[y][x].x_pos = (y * sqrt(3) + x * sqrt(3)) * 10;
		axis[y][x].y_pos = (y - x) * 10;
		axis[y][x].alt = ft_atoi(spl[x]) * 10;
		x++;
	}
	axis[y][x].x_pos = end;
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
		if (!line_to_axis(line_list -> content, axis_arr, y))
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
void	del_free(void *ptr)
{
	free((char *)ptr);
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