/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 19:23:03 by woojeong          #+#    #+#             */
/*   Updated: 2022/07/29 12:33:19 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> ////////////////////////
#include <stdlib.h>
#include <unistd.h>

typedef struct  s_read_list{
    char    str[BUFF_SIZE + 1];
    struct  s_read_list *next;
} t_read_list;

typedef struct  s_fd_list{
    int     fd;
    char    str[BUFF_SIZE + 1];
    struct  s_fd_list *next;
} t_fd_list;

int read_free(t_read_list *list);
int read_file_until_nl(int fd, int *line_len, t_fd_list **remain_box, t_read_list *read_list);
int cpy_until_nl(char *str, char *buff, char *remain_str, int read_len);
char    *make_new_line(int line_len, t_read_list *read_list);
char    *get_next_line(int fd);
void    fd_free(int fd, t_fd_list **remain_box);
t_fd_list   *search_fd_in_box(t_fd_list **box, int fd);
int new_fd_box(int fd, t_fd_list **box);
int pull_from_box(char *remain_str, t_fd_list *box);
int check_fd_remain_box(t_fd_list **remain_box, char *remain_str,int fd);