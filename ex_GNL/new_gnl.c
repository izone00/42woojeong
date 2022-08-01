/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:01:12 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/29 13:34:35 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
fd_box 만들기
dup str to read_list 
update fd_box -> str
read file
update fd_box -> str
dup str to line
*/
#include "new_gnl.h"

char *get_next_line(int fd)
{
	static t_fd_list    *fd_lst;
	t_fd_list			*cur_fd;
	t_read				read_lst;
	int                 line_len;

	(read_lst.str[0]) = '\0';
	read_lst.next = NULL;
	if ((cur_fd = find_fd(&fd_lst, fd)) == NULL)
		return (NULL);
	line_len = cpy_until_nl(read_lst.str, cur_fd -> str);
	update_fd(cur_fd -> str, (char *)(cur_fd -> str) + line_len);
	if (line_len == 0 || (read_lst.str)[line_len - 1] != '\n')
	{
		if ((read_until_nl(&read_lst, cur_fd, fd, &line_len)) == 0 || line_len == 0)
		{
			fd_free();
			return (NULL);
		}
	}
	make_new_line();
}

int read_until_nl(t_read *lst, t_fd_list *cur_fd, int fd, int *line_len)
{
	char        buff[BUFF_SIZE + 1];
	int         read_len;
	t_read		*cur;

	cur = lst;
	while (0 < (read_len = read(fd, buff, BUFF_SIZE)))
	{
		buff[read_len] = '\0';
		if (!(cur -> next = (t_read *)malloc(sizeof(t_read))))
			return (read_free()); // mem err
		cur = cur -> next;
		(cur -> str)[0] = '\0';
		cur -> next = NULL;
		read_len = cpy_until_nl(cur -> str, buff);// 여기서 read_len > 0 을 보장 -> line_len > 0도 보장
		*line_len += read_len;
		update_fd(cur_fd -> str, buff + read_len); //정상적으로 읽다가 eof로 끝날때 cur -> str은 빈 문자열임을 보장
		if ((cur_fd -> str)[read_len - 1] == '\n')//read_len > 1을 보장받을 수 있어야한다. 아마 보장될듯
			return (1);
	}
	if (read_len < 0)// file read err
		return (read_free());
	//밖으로 빼고 싶다...
	fd_free();//eof로 정상종류 && cur_fd -> str은 빈 문자열임을 보장 받아야 할수있다.
	return (1);
}