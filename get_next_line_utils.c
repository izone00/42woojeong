/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 18:53:04 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/28 19:24:10 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int check_fd_remain_box(t_fd_list **remain_box, char *remain_str,int fd)
{
    t_td_list   *box;
    int         remain_len;

    if (*remain_box == NULL)
    {
        if (new_fd_box(fd, remain_box) == '-1')//(-1)은 mem_err
            return (-1);
        box = *remain_box;
    }
    else
    {
        box = *remain_box;
        if(!search_fd_in_box(&box, fd))
        {
            if (new_fd_box(fd, &(box -> next)))
                return (-1);
        }
    }
    remain_len = pull_from_box(remain_str, box);
    return (remain_len);
}
//remain_str에 복사해주고 box도 수정해준다

int pull_from_box(char *remain_str, t_fd_list *box)
{
    int len;
    int dest;

    len = 0;
    while ((box -> str)[len])
    {
        remain_str[len] = (box -> str)[len];
        if (remain_str[len] == '\n')
        {
            len++;
            break;
        }
        len++;
    }
    remain[len] ='\0';
    dest = 0;
    while ((box -> str)[len + dest])
    {
        (box -> str)[dest] = (box -> str)[len + dest];
        dest++;
    }
    (box -> str)[dest] = '\0'
    return (len);
}

int new_fd_box(int fd, t_fd_list **box)
{
    *box = (t_fd_list *)malloc(sizeof(t_fd_list));
    if (*box == NULL)
        return (-1);
    (*box) -> next = NULL;
    (*box) -> fd = fd;
    ((*box) -> str)[0] = '\0';
    return (1);
}
void    fd_free(int fd, t_fd_list **remain_box)
t_fd_list   *search_fd_in_box(t_fd_list **box, int fd)
{
    while ((*box) -> next != NULL)
    {
        if ((*box) -> fd == fd)
            return (*box);
        (*box) = (*box) -> next;
    }
    if ((*box) -> fd == fd)
        return (*box);
    else
        return (0);
}

void    fd_free(int fd, t_fd_list **remain_box)
{
    t_fd_list *pre;
    t_fd_list *cur;

    cur = *remain_box;
    if (cur -> fd == fd)
    {
        *remain_box = (*remain_box) -> next;
        free(cur);
    }
    while (cur)
    {
        pre = cur;
        cur = cur -> next;
        if (cur -> fd == fd)
        {
            pre -> next = cur -> next;
            free(cur);
            return;
        }
    }
}