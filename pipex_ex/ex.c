#include <stdio.h>//perror
#include <string.h>//strerror
#include <unistd.h>//access

#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#define BUFF_SIZE 3

int	main()
{
	char buff[11];
	int fd1 = open("./in1", O_RDONLY);
	int fd2 = 10;
	int fd3 = 20;
	int read_len;
	int pid;
	int stat;
	int pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid != 0)
		printf("[1. %d %d]\n", pipefd[0], pipefd[1]);
	if (pid == 0)
	{
		write(pipefd[1], "pipe\n", 5);
		// close(pipefd[1]);
	}
	else
	{
		wait(&stat);
		dup2(pipefd[0], fd2);
		close(pipefd[0]);
		read_len = read(fd2, buff, BUFF_SIZE);
		write(1, buff, read_len);
		// dup2(pipefd[1], fd3);
		close(pipefd[1]);
		close(fd2);
		// close(fd3);
		int pip = pipe(pipefd);
		if ((-1) == write(pipefd[1], "second\n", 6))
			write(1, "write fail\n", 11);
		read_len = read(pipefd[0], buff, BUFF_SIZE);
		printf("[read len : %d]\n", read_len);
		write(1, buff, read_len);
		printf("[2. %d %d]\n", pipefd[0], pipefd[1]);
		printf("[%d]\n", pip);
	}
	// dup2(fd1, fd2);
	// close(fd1);
	// read_len = read(fd2, buff, BUFF_SIZE);
	// buff[read_len] = '\0';
	// write(1, buff, read_len);


}