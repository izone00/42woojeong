#include <stdio.h>//perror
#include <string.h>//strerror
#include <unistd.h>//access

#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
enum pipe_num {
	r = 0,
	out = 0,
	w = 1,
	in = 1
};

#define BUFF_SIZE 5

int	main()
{
	char	buff[10];
	int		pipefd[2];
	int		pipefd2[2];

	pipe(pipefd);
	write(pipefd[w], "hello world", 11);
	pipe(pipefd2);
	close(pipefd[w]);
	close(pipefd[r]);
	printf("pipe1 : %d %d\n", pipefd[r], pipefd[w]);
	pipe(pipefd);
	printf("pipe1 : %d %d\n", pipefd[r], pipefd[w]);
	close(pipefd[w]);
	printf("pipe1 : %d %d\n", pipefd[r], pipefd[w]);
	int	read_len = 0;
	while ((read_len = read(pipefd[r], buff, BUFF_SIZE)) > 0)
	{
		write(pipefd2[w], buff, read_len);
		write(1,"pipe1\n", 6);
	}
	close(pipefd2[w]);
	while ((read_len = read(pipefd2[r], buff, BUFF_SIZE)) > 0)
	{
		write(1, buff, read_len);
	}
}