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
#include "ex_get_next_line.h"

char    *get_next_line(int fd)  
{
    static      t_fd_list *remain_box;
    t_read_list read_list;
    int         line_len;

    (read_list.str)[0] = '\0';
    read_list.next = NULL;
    // new fd box 생성 box -> str 을 수정하기 위해 주소 전달
    line_len = check_fd_remain_box(&remain_box, read_list.str, fd);// malloc current fd_box
    if (line_len == (-1))
        return (NULL);
    if (line_len == 0 || (read_list.str)[line_len - 1] != '\n')
    {
        //line_len 수정을위해 주소 전달, reamin_box 수정, free를 위해 전달, read_list 수정을 위해 전달
        if (read_file_until_nl(fd, &line_len, &remain_box, &read_list) == (-1)) // free current fd_box when read err, malloc read_list
            return (NULL);
    }
    if (line_len == 0)
        return (NULL);
    return (make_new_line(line_len, &read_list)); // free read_list
}
//input
// fd : (good fd, bad fd, eof fd)
// line_len(>=0) : (지금까지 읽은 길이)
// remain_box : (현재 fd값에 해당하는 box를 malloc 받은 상태, str이 빈문자열인 상태)
int read_file_until_nl(int fd, int *line_len, t_fd_list **p_remain_box, t_read_list *read_list)
{
    char    buff[BUFF_SIZE];
    int         read_len;
    t_fd_list *cur_fd_box;
    t_read_list *cur_read;

    cur_read = read_list; // read_list free를 위해 시작점을 알고있어야함
    cur_fd_box = *p_remain_box;
    cur_fd_box = search_fd_in_box(&cur_fd_box, fd); ///////////////////////////////////불만
    while (0 < (read_len = read(fd, buff, BUFF_SIZE))) // is good fd ?
    {
        *line_len += read_len;
        cur_read -> next = (t_read_list *)malloc(sizeof(t_read_list));
        cur_read = cur_read -> next;
        if (cur_read == NULL)
        {
            fd_free(fd, p_remain_box); // 파일을 읽었는데 malloc 실패하면 이어지지 않으므로 남은게 의미없다.
            return (read_free(read_list -> next)); // return (-1)
        }
        (cur_read -> str)[0] = '\0';
        cur_read -> next  = NULL;
        if (cpy_until_nl(cur_read -> str, buff, cur_fd_box -> str, read_len))
            return (1);
    }
    fd_free(fd, p_remain_box); // eof fd, bad fd, good fd(but 이 함수에서 파일을 끝까지 읽고 eof도달)
    return (1);
}

char    *make_new_line(int line_len, t_read_list *read_list)
{
    t_read_list *cur_read;
    int         idx;
    int         jdx;
    char        *line;

    if ((line = (char *)malloc(line_len + 1)) == NULL)
    {
        read_free(read_list -> next);
        return (NULL);
    }
    line[0] = '\0';
    cur_read = read_list;
    idx = 0;
    while (cur_read)
    {
        jdx = 0;
        while ((cur_read -> str)[jdx])
            line[idx++] = (cur_read -> str)[jdx++];
        line[idx] = '\0';
        cur_read = cur_read -> next;
    }
    read_free(read_list -> next);
    return (line);
}
//input
// read : 빈 문자열
// buff : 읽은 문자들의 배열(!문자열)
// remain : 현재 fd_box의 문자열(빈 문자열)
// buff_len : buff배열 길이
int cpy_until_nl(char *read, char *buff, char *remain, int buff_len)
{
    int idx;
    int jdx;

    idx = 0;
    while (idx < buff_len)
    {
        read[idx] = buff[idx];
        if (read[idx] == '\n')
        {
            jdx = 0;
            idx++;
            read[idx] = '\0';
            while (idx < buff_len)
            {
                remain[jdx] = buff[idx];
                idx++;
                jdx++;
            }
            remain[jdx] = '\0';
            return (1);
        }
        idx++;
    }
    read[idx] = '\0';
    return (0);
}

int read_free(t_read_list *list)
{
    t_read_list *pre;

    while (list)
    {
        pre = list;
        list = list -> next;
        free(pre);        
    }
    return (-1);
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
    // if ((str = get_next_line(10)) == NULL)
    //     printf("is NULL\n");
    while (i <= 8)
    {
        str = get_next_line(fd1);
        if (!str)
            break;
        printf("(fd1) %d: %s/\n", i, str);
        //free(str);
        str = get_next_line(fd2);
        if (!str)
            break;
        printf("(fd2) %d: %s/\n", i, str);
        //free(str);
        str = get_next_line(fd3);
        if (!str)
            break;
        printf("(fd3) %d: %s/\n", i, str);
        //free(str);
        i++;
    }
}
