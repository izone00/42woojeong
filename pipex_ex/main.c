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
	char	filename2[20] = "/usr/bin/";
	char	**command1;
	char	**command2;
	char	buff[11];
	int		read_len;
	int		stat;
	int		fd[2];
	int		fd1;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		fd1 = open(argv[1], O_RDONLY);//argv[1]는 정확한 경로를 전달해 준다.
		command1 = ft_split(argv[2], ' ');
		strcat(filename1, command1[0]);
		dup2(fd1, 0);// 0 -> fd1
		dup2(fd[1], 1);
		execve(filename1, command1, environ);
	}
	wait(&stat);
	dup2(fd[0], 0);
	command2 = ft_split(argv[3], ' ');
	strcat(filename2, command2[0]);
	execve(filename2, command2, environ);
	perror("err");
}