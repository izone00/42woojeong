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
