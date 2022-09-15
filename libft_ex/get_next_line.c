/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:57:58 by woojeong          #+#    #+#             */
/*   Updated: 2022/08/04 17:27:00 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_fd_list	*save;
	t_fd_list			*save_fd;
	t_read				read_lst;
	int					line_len;
	char				*line;

	(read_lst.str[0]) = '\0';
	read_lst.next = NULL;
	save_fd = find_fd(&save, fd);
	if (!save_fd)
		return (NULL);
	line_len = cpy_until_nl(read_lst.str, save_fd -> str);
	update_save(save_fd -> str, (char *)(save_fd -> str) + line_len);
	if (line_len == 0 || (read_lst.str)[line_len - 1] != '\n')
	{
		if (!read_until_nl(&read_lst, save_fd, fd, &line_len) || !line_len)
		{
			fd_free(&save, fd);
			return (NULL);
		}
	}
	line = make_new_line(read_lst, line_len);
	if (!line || ((save_fd -> str)[0] == '\0'))
		fd_free(&save, fd);
	return (line);
}

t_fd_list	*find_fd(t_fd_list **p_save, int fd)
{
	t_fd_list	*cur;
	t_fd_list	*pre;

	if (*p_save == NULL)
	{
		if (!new_fd(fd, p_save))
			return (NULL);
		return (*p_save);
	}
	else
	{
		cur = *p_save;
		while (cur)
		{
			pre = cur;
			if (cur -> fd == fd)
				return (cur);
			cur = cur -> next;
		}
		if (!new_fd(fd, &(pre -> next)))
			return (NULL);
		return (pre -> next);
	}
}

int	new_fd(int fd, t_fd_list **p_cur)
{
	*p_cur = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (!(*p_cur))
		return (0);
	(*p_cur)-> fd = fd;
	((*p_cur)-> str)[0] = '\0';
	(*p_cur)-> next = NULL;
	return (1);
}

int	read_until_nl(t_read *p_lst, t_fd_list *save_fd, int fd, int *line_len)
{
	char		buff[BUFFER_SIZE + 1];
	int			read_len;
	t_read		*cur;

	cur = p_lst;
	read_len = read(fd, buff, BUFFER_SIZE);
	while (0 < read_len)
	{
		buff[read_len] = '\0';
		cur -> next = (t_read *)malloc(sizeof(t_read));
		if (!(cur->next))
			return (read_free(*p_lst));
		cur = cur -> next;
		(cur -> str)[0] = '\0';
		cur -> next = NULL;
		read_len = cpy_until_nl(cur -> str, buff);
		*line_len += read_len;
		update_save(save_fd -> str, buff + read_len);
		if ((cur -> str)[read_len - 1] == '\n')
			return (1);
		read_len = read(fd, buff, BUFFER_SIZE);
	}
	if (read_len < 0)
		return (read_free(*p_lst));
	return (1);
}

char	*make_new_line(t_read lst, int line_len)
{
	t_read	*cur;
	char	*line;
	int		idx;
	int		jdx;

	line = (char *)malloc(sizeof(char) * (line_len + 1));
	if (!line)
	{
		read_free(lst);
		return (NULL);
	}
	idx = 0;
	cur = &lst;
	while (cur)
	{
		jdx = 0;
		while ((cur -> str)[jdx])
			line[idx++] = (cur -> str)[jdx++];
		cur = cur -> next;
	}
	line[idx] = '\0';
	read_free(lst);
	return (line);
}
