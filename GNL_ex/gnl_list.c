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
    static  char remain[BUFF_SIZE + 1];//현재함수가 실행될때 사용되는 짜투리문자열을 담아두는곳 (remain_box에서 복사해온다)
    char        dup[BUFF_SIZE + 1];
    int         is_nl;
    static  t_fd_list *remain_box;//각 fd에 대해 남아있는 짜투리들이 담긴 박스
    t_fd_list   *ptr_remain;

    check_fd(&remain_box, &ptr_remain, fd);//check_fd사용 이후에 box는 fd의 나머지로 차있고 ptr_remain은 해당하는 나머지를 복사해 가지고 있는다.
    //printf("fd : %d, remain : %s   ", ptr_remain -> fd, ptr_remain -> str);
    is_nl = 0;
    total_len = len_until_nl(ptr_remain -> str, dup, &is_nl);//ptr_remain에서 엔터키나 문자열의 끝을 찾아 dup에 복사하고 길이를 리턴한다.
    lst = NULL;
    if (is_nl)//ptr_remain에 엔터키가 있었다면 거기부터 ptr_remain의 인덱스를 당긴다.
        memmove(ptr_remain -> str, ptr_remain -> str + total_len, strlen(ptr_remain -> str) - total_len + 1);
    else if (0 < (read_len = read(fd, buff, BUFF_SIZE)))
    {
        cur_read = (t_list *)malloc(sizeof(t_list));//현재읽은 문자열을 담기위해 리스트를 만든다.
        lst = cur_read;
        cur_read -> next = 0;
        if (!cpy_until_nl(cur_read -> str, buff, read_len, ptr_remain -> str))//엔터키나 버퍼끝까지 읽고 유효한부분을 cur->str에 담고 나머지를 ptr_remain에 담는다.
        {   //엔터키를 발견했을못했을때
            while (0 < (read_len = read(fd, buff, BUFF_SIZE)))//파일끝까지 읽는다.
            {
                cur_read -> next = (t_list *)malloc(sizeof(t_list));//리스트 넥스트에 칸을 마련한다.
                cur_read = cur_read -> next;
                cur_read -> next = 0;
                total_len += read_len;//넉넉하게 엔터키 상관없이 total_len을 확보한다.
                if (cpy_until_nl(cur_read -> str, buff, read_len, ptr_remain -> str)) //위와동일하게 복사하고 엔터키찾으면 탈출
                    break;
            }
        }
    }
    else
    {
        fd_free(&remain_box, ptr_remain, fd);//파일끝이나 파일오류면 해당 fd의 박스를 프리하고 나머지 fd를 연결한다.
        return (NULL);
    }
    rst = (char *)malloc(sizeof(char) * (total_len + 1));
    read_len = 0;
    while (dup[read_len])//이전에 남아 있던 자투리를 복사한다.
    {
        rst[read_len] = dup[read_len];
        read_len++;
    }
    rst[read_len] = '\0';
    while (lst) //이번에 읽은 문자열을 붙인다.
    {
        read_len += memcat(rst + read_len, lst -> str);
        cur_read = lst;
        lst = lst -> next;
        free(cur_read); //이번에 읽으면서 만든 문자열 리스트를 프리한다.
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
//check_fd는 remain_box의 fd값을 확인해서 남아있는 문자열을 ptr에 넣어준다
//이때 box에 fd에 해당하는 칸이 없다면 fd에 해당하는 칸를 만들어야한다
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
