/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 20:01:12 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/28 19:23:42 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *get_next_line(int fd)  
{
    static      t_fd_list *remain_box;//이전에 남은 remain들의 box 자동으로 '0'초기화
    // char        remain_str[BUFF_SIZE + 1];//해당 fd에서 가져온 remain을 담은 str
    t_read_list read_list;
    char        *line;
    int         line_len;

    //사용할 remain이 있는지, 새로운 fd_box를 만들지, 원하는 만큼 from_remain에 복사 해둔다, remain_box를 수정한다.
    (read_list.str).[0] = '\0';
    read_list.next = NULL;
    line_len = check_fd_remain_box(&remain_box, &(read_list.str), fd);
    if (line_len == (-1))
        return (NULL);
    //실행후에는 remain_box에서 정보를 사용하고 수정되어있고 from_remain에는 사용할 문자열이 담긴다.
    if ((read_list.str)[line_len - 1] != '\n')//엔터키가 없어 더 읽어야한다면
    {
        if (read_file_until_nl(fd, &line_len, &remain_box, &read_list) == (-1))
            return (NULL);
    }
    //위 함수들이 실행된 이후에는 최종 line의 길이, 이전 문자열, 새로 읽은 문자열 리스트가 설정되고 읽다가 남은 문자열을 box에 저장한다.
    line = (char *)malloc(line_len + 1);
    if (line = NULL)
    {
        read_free(read_list);
        return (NULL);
    }
    line[0] = '\0';
    //ft_strcat(line, remain_str);
    make_new_line(line, &read_list);
    return (line);
}

void    make_new_line(char *line, t_read_list *read_list)
{
    t_read_list *cur_read;
    int idx;
    int jdx;

    cur_read = read_list;
    idx = 0;
    while (cur_read)
    {
        jdx = 0;
        while ((cur_read -> str)[jdx])
        {
            line[idx] = (cur_read -> str)[jdx]);
            idx++;
            jdx++;
        }
        line[idx] = '\0';
        cur_read = cur_read -> next;
    }
    read_free(read_list -> next);// cpy함수 안에서 해도됨
}

int cpy_until_nl(char *str, char *buff, char remain_str, int read_len)
{
    int idx;
    int jdx;

    idx = 0;
    while (idx < read_len)
    {
        str[idx] = buff[idx];
        if (str[idx] == '\n')
        {
            jdx = 0;
            idx++;
            while (idx < read_len)
            {
                remain_str[jdx] = read_len[idx];
                idx++;
                jdx++;
            }
            remain_str[jdx] = '\0';
            return (1);
        }
        idx++;
    }
    str[idx] = '\0';
    return (0);
}

int read_file_until_nl(int fd, int *line_len, t_fd_list **remain_box, t_read_list *read_list)
{
    char    buff[BUFF_SIZE];
    int         read_len;
    t_read_list *cur_fd_box;

    cur_read = read_list;
    cur_fd_box = search_fd_in_box(remain_box, fd);
    while (0 < (read_len = read(fd, buff, BUFF_SIZE)))
    {
        *line_len += read_len;
        cur_read -> next = (t_read_list *)malloc(sizoeof(t_read_list));
        cur_read = cur_read -> next;
        if (cur_read == NULL)
            return (read_free(read_list -> next));
        (cur_read -> str)[0] = '\0';
        cur_read -> next  = NULL;
        if (cpy_until_nl(cur_read -> str, buff, cur_fd_box -> str, read_len))
            return (1);//nl이 있었으면 1을 반환
    }
    if (read_len <= 0)
    {
        fd_free(fd, remain_box);// 밖으로 빼야할듯? ㄴㄴ
        return (1);
    }
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