#include <stdio.h>//perror
#include <string.h>//strerror
#include <unistd.h>//access

#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
char	**ft_split(char const *s, char c);

// extern int errno;
extern char	**environ;
#define BUFF_SIZE 10

int main(int argc, char *argv[])
{
	char	filename[20] = "/bin/";
	char	**command;
	int		fd1;
	char	buff[11];
	int		read_len;

	command = ft_split(argv[2], ' ');
	strcat(filename, command[0]);

	fd1 = open(argv[1], O_RDONLY);//argv[1]는 정확한 경로를 전달해 준다.
	dup2(fd1, 0);
	execve(filename, command, environ);
	perror("err");
}