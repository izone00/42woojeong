/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gnl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:57:58 by woojeong          #+#    #+#             */
/*   Updated: 2022/08/02 14:12:13 by woojeong         ###   ########.fr       */
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
	char				*line;

	(read_lst.str[0]) = '\0';
	read_lst.next = NULL;
	if (!(cur_fd = find_fd(&fd_lst, fd)))//현재fd에 대한 cur_fd의 존재를 보장
		return (NULL);
	// printf("[cur fd -> %d, str -> (%s)]\n", cur_fd -> fd, cur_fd -> str);
	line_len = cpy_until_nl(read_lst.str, cur_fd -> str);
	// printf("[line_len = %d]\n", line_len);
	update_fd(cur_fd -> str, (char *)(cur_fd -> str) + line_len);
	// printf("[remain : (%s)]\n", cur_fd -> str);
	if (line_len == 0 || (read_lst.str)[line_len - 1] != '\n')
	{
		if (!read_until_nl(&read_lst, cur_fd, fd, &line_len) || !line_len)// 오류가 났을때 read_free만하고 나온다.
		{
			fd_free(&fd_lst, fd);
			return (NULL);
		}
	}
	if (!(line = make_new_line(read_lst, line_len)))// 이 아래에서는 read_free가 된 상태
		fd_free(&fd_lst, fd);// 오류에 의한 fd_free
	else if ((cur_fd -> str)[0] == '\0')
		fd_free(&fd_lst, fd);// 모든게 완벽히 성공했을떄 fd_free
	return (line);
	// return (NULL);
}

t_fd_list	*find_fd(t_fd_list **p_fd_lst, int fd)
{
	t_fd_list	*cur;

	if (*p_fd_lst == NULL)
	{
		// printf("fd new\n");
		if (!new_fd(fd, p_fd_lst))
			return (NULL);
		return (*p_fd_lst);
	}
	else
	{
		// printf("fd old\n");
		cur = *p_fd_lst;
		while (cur -> next)// 마지막으로 있는 fd는 검사 못한다
		{
			if (cur -> fd == fd)
				return (cur);
			cur = cur -> next;
		}
		if (cur -> fd != fd)// 마지막 fd를 검사
		{
			if(!new_fd(fd, &(cur -> next)))
				return (NULL);
			cur = cur -> next;
		}
		return (cur);
	}
}

int	new_fd(int fd, t_fd_list **p_cur)
{
	if (!(*p_cur = (t_fd_list *)malloc(sizeof(t_fd_list))))
		return (0);
	(*p_cur) -> fd = fd;
	((*p_cur) -> str)[0] = '\0';
	(*p_cur) -> next = NULL;
	return (1);
	
}

int read_until_nl(t_read *p_lst, t_fd_list *cur_fd, int fd, int *line_len)
{
	char        buff[BUFF_SIZE + 1];
	int         read_len;
	t_read		*cur;

	cur = p_lst;
	while (0 < (read_len = read(fd, buff, BUFF_SIZE)))
	{
		buff[read_len] = '\0';
		if (!(cur -> next = (t_read *)malloc(sizeof(t_read))))
			return (read_free(*p_lst)); // mem err
		cur = cur -> next;
		(cur -> str)[0] = '\0';
		cur -> next = NULL;
		read_len = cpy_until_nl(cur -> str, buff);// 여기서 read_len > 0 을 보장 -> line_len > 0도 보장
		*line_len += read_len;
		update_fd(cur_fd -> str, buff + read_len); //정상적으로 읽다가 eof로 끝날때 cur -> str은 빈 문자열임을 보장
		// printf("[lst : (%s), fd : (%s)]\n", cur -> str, cur_fd -> str);
		if ((cur -> str)[read_len - 1] == '\n')//read_len > 0을 보장받을 수 있어야한다. 아마 보장될듯
			return (1);
	}
	if (read_len < 0)// file read err
		return (read_free(*p_lst));
	else
		return (1);
}

char	*make_new_line(t_read lst, int line_len)
{
	t_read	*cur;
	char	*line;
	int		idx;
	int		jdx;

	if (!(line = (char *)malloc(sizeof(char)* (line_len + 1))))
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



#include <fcntl.h>
int main()
{
    int fd1;
    int fd2;
    char *str;
    int i = 1;

    fd1 = open("./test.txt", O_RDONLY);
    fd2 = open("./test2.txt", O_RDONLY);
    int fd3= open("./test3.txt", O_RDONLY);
	int fd4 = open("./test4.txt", O_RDONLY);
    // if ((str = get_next_line(10)) == NULL)
    //     printf("is NULL\n");
    while (i <= 20)
    {
        str = get_next_line(fd1);
        printf("(fd1) %d: /%s/ ", i, str);
        //free(str);
        str = get_next_line(fd2);
        // if (!str)
        //     break;
        printf("(fd2) %d: /%s/ ", i, str);
        // //free(str);
        str = get_next_line(fd3);
        // if (!str)
        //     break;
        printf("(fd3) %d: /%s/ ", i, str);
        //free(str);
		str = get_next_line(fd4);
		printf("(fd4) %d: /%s/ \n", i, str);
        i++;
    }
}
