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
	pid_t	pid;
	char	filename1[20] = "/bin/";
	char	filename2[20] = "/bin/";
	char	**command1;
	char	**command2;
	int		fd1;
	char	buff[11];
	int		read_len;
	int		stat;

	command1 = ft_split(argv[2], ' ');
	strcat(filename1, command1[0]);

	fd1 = open(argv[1], O_RDONLY);//argv[1]는 정확한 경로를 전달해 준다.
	int	fd_out;
	fd_out = dup(1); //fd_out = stdout
	dup2(0, 1);//1 -> stdin
	dup2(fd1, 0);// 0 -> fd1
	pid = fork();
	if (pid == 0)
		execve(filename1, command1, environ);
	wait(&stat);
	dup2(fd_out, 1);// 1 -> stdout
	command2 = ft_split(argv[3], ' ');
	strcat(filename2, command2[0]);
	execve(filename2, command2, environ);
	perror("err");
}