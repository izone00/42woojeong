#include <stdlib.h>
#include <unistd.h>
#include <string.h>//////////
#include <stdio.h> ////////////////////////////


typedef struct s_list{
    char str[BUFF_SIZE + 1];
    struct s_list *next;
} t_list;

typedef struct s_fd_list{
    int     fd;
    char    str[BUFF_SIZE + 1];
    struct  s_fd_list *next;
} t_fd_list;

size_t    memcat(char *rst, char *str);
int cpy_until_nl(char *str, char *buff, size_t len, char *remain);
size_t  len_until_nl(char *remain, char *dup, int *is_nl);
void    check_fd(t_fd_list **remain_box, t_fd_list **ptr, int fd);
void    fd_free(t_fd_list **remain_box, t_fd_list *ptr_remain, int fd);

char    *get_next_line(int fd)
{
    t_list  *cur_read;
    t_list  *lst;
    size_t     read_len;
    size_t     total_len;
    char    buff[BUFF_SIZE];
    char    *rst;
    static  char remain[BUFF_SIZE + 1];
    char        dup[BUFF_SIZE + 1];
    int         is_nl;
    static  t_fd_list *remain_box;
    t_fd_list   *ptr_remain;

    check_fd(&remain_box, &ptr_remain, fd);
    //printf("fd : %d, remain : %s   ", ptr_remain -> fd, ptr_remain -> str);
    is_nl = 0;
    total_len = len_until_nl(ptr_remain -> str, dup, &is_nl);
    lst = NULL;
    if (is_nl)
        memmove(ptr_remain -> str, ptr_remain -> str + total_len, strlen(ptr_remain -> str) - total_len + 1);
    else if (0 < (read_len = read(fd, buff, BUFF_SIZE)))
    {
        cur_read = (t_list *)malloc(sizeof(t_list));
        lst = cur_read;
        cur_read -> next = 0;
        if (!cpy_until_nl(cur_read -> str, buff, read_len, ptr_remain -> str))
        {
            while (0 < (read_len = read(fd, buff, BUFF_SIZE)))
            {
                cur_read -> next = (t_list *)malloc(sizeof(t_list));
                cur_read = cur_read -> next;
                cur_read -> next = 0;
                total_len += read_len;
                if (cpy_until_nl(cur_read -> str, buff, read_len, ptr_remain -> str))
                    break;
            }
        }
    }
    else
    {
        fd_free(&remain_box, ptr_remain, fd);
        return (NULL);
    }
    rst = (char *)malloc(sizeof(char) * (total_len + 1));
    read_len = 0;
    while (dup[read_len])
    {
        rst[read_len] = dup[read_len];
        read_len++;
    }
    rst[read_len] = '\0';
    while (lst)
    {
        read_len += memcat(rst + read_len, lst -> str);
        cur_read = lst;
        lst = lst -> next;
        free(cur_read);
    }
    return (rst);
}

void    fd_free(t_fd_list **remain_box, t_fd_list *ptr_remain, int fd)
{
    t_fd_list *pre_list;

    pre_list = *remain_box;
    if (pre_list -> fd == fd)
    {
        (*remain_box) = (*remain_box) -> next;
        free(ptr_remain);
        return ;
    }
    while (pre_list -> next != ptr_remain)
        pre_list = pre_list -> next;
    pre_list -> next = ptr_remain -> next;
    free(ptr_remain);
}

size_t  len_until_nl(char *remain, char *dup, int *is_nl)
{
    size_t  len;

    len = 0;
    while (remain[len])
    {
        dup[len] = remain[len];
        if (remain[len] == '\n')
        {
            *is_nl = 1;
            dup[len + 1] = '\0';
            return (len + 1);
        }
        len++;
    }
    dup[len] = '\0';
    return (len);
}

size_t  memcat(char *rst, char *str)
{
    size_t idx;

    idx = 0;
    while (str[idx])
    {
        rst[idx] = str[idx];
        idx++;
    }
    rst[idx] = '\0';
    return (idx);
}

int cpy_until_nl(char *str, char *buff, size_t len, char *remain)
{
    size_t idx;

    idx = 0;
    while (idx < len)
    {
        str[idx] = buff[idx];
        if (buff[idx] == '\n')
        {
            str[idx + 1] = '\0';
            int jdx = 0;
            idx++;
            while (idx < len)
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
    str[idx] = '\0';
    return (0);
}

void    check_fd(t_fd_list **remain_box, t_fd_list **ptr, int fd)
{
    t_fd_list *cur;

    cur = *remain_box;
    if (*remain_box == NULL)
    {
        (*remain_box) = malloc(sizeof(t_fd_list));
        *ptr = *remain_box;
        (*ptr) -> next = NULL;
        (*ptr) -> fd = fd;
        ((*ptr) -> str)[0] = '\0';
    }
    else
    {
        while (cur -> next != NULL)
        {
            if (fd == cur -> fd)
            {
                *ptr = cur;
                return;
            }
            cur = cur -> next;
        }
        if (fd == cur -> fd)
        {
            *ptr = cur;
            return;
        }
        cur -> next = malloc(sizeof(t_fd_list));
        *ptr = cur -> next;
        (*ptr) -> next = NULL;
        (*ptr) -> fd = fd;
        ((*ptr) -> str)[0] = '\0';
    }
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
    while (str = get_next_line(fd1))
    {
        printf("(fd1) %d:%s /\n", i, str);
        free(str);
        str = get_next_line(fd2);
        printf("(fd2) %d:%s /\n", i, str);
        free(str);
        str = get_next_line(fd3);
        printf("(fd3) %d:%s /\n", i, str);
        free(str);
        i++;
    }
}
