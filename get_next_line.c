#include <stdlib.h>
#include <unistd.h>
#include <string.h>//////////
#include <stdio.h> ////////////////////////////


int check_nl(char *buff, int read_len);

char    *get_next_line(int fd)
{
    int     read_len;
    char    buff[BUFF_SIZE + 1];
    char    *line;
    char    *pre_line;
    int     mal_volume;
    int     nl_exist;
    
    pre_line = (char *)malloc(sizeof(char));
    pre_line[0] = '\0';
    mal_volume = 0;
    line = (char *)malloc(sizeof(char));
    line[0] = '\0';
    nl_exist = 0;
    while (0 < (read_len = read(fd, buff, BUFF_SIZE)) && !nl_exist)
    {
        mal_volume = mal_volume + read_len + 1;
        free(line);
        line = (char *)malloc(sizeof(char) * mal_volume);
        line[0] = '\0';
        strcat(line, pre_line);
        nl_exist = check_nl(buff, read_len);
        strcat(line, buff);
        free(pre_line);
        pre_line = (char *)malloc(sizeof(char) * mal_volume);
        pre_line[0] = '\0';
        strcat(pre_line, line);
    }
    free(pre_line);
    if (read_len == 0)
        printf("file end\n");
    else if (read_len < 0)
        printf("file error\n");
    return (line);
}

int check_nl(char *buff, int read_len)
{
    int idx;

    idx = 0;
    while (idx < read_len)
    {
        if (buff[idx] == '\n')
        {
            buff[idx + 1] = '\0';
            return (1);
        }
        idx++;
    }
    buff[read_len] = '\0';
    return (0);
}

#include <fcntl.h>
int main()
{
    int fd;

    fd = open("./test.txt", O_RDONLY);
    printf("%s\n", get_next_line(fd));
}
