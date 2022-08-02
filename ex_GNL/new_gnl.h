/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_gnl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:57:50 by woojeong          #+#    #+#             */
/*   Updated: 2022/08/02 10:57:51 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> ////////////////////////
#include <stdlib.h>
#include <unistd.h>

typedef struct  s_read_list{
    char    str[BUFF_SIZE + 1];
    struct  s_read_list *next;
} t_read;

typedef struct  s_fd_list{
    int     fd;
    char    str[BUFF_SIZE + 1];
    struct  s_fd_list *next;
} t_fd_list;

int read_until_nl(t_read *p_lst, t_fd_list *cur_fd, int fd, int *line_len);
int	read_free(t_read lst);
int	new_fd(int fd, t_fd_list **p_cur);
t_fd_list	*find_fd(t_fd_list **p_fd_lst, int fd);
int	cpy_until_nl(char *dest, char *src);
void	update_fd(char *dest, char *src);
void	fd_free(t_fd_list **p_fd_lst, int fd);
char	*make_new_line(t_read lst, int line_len);
char *get_next_line(int fd);