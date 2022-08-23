#include <stdio.h>//perror
#include <string.h>//strerror
#include <unistd.h>//access

#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
char	**ft_split(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_strlen(const char *str);

#define BUFF_SIZE 10

int main(int argc, char *argv[], char *envp[])//env는 null terminate되있다.
{
	int		read_len;
	char	buff[11];

	pid_t	pid;
	char	**command1;
	char	**command2;
	char	**filepath;
	char	filename1[30];
	char	filename2[30];
	int		stat;
	int		pipefd[2];
	int		fd1;
	int		fd2;
	int		idx;

	idx = 0;
	filepath = NULL;
	while (envp[idx])
	{
		if (!ft_strncmp("PATH=", envp[idx], 5))
			filepath = ft_split(envp[idx], ':');
		idx++;
	}
	if (!filepath)
		perror("no PATH"); // PATH경로가 없을때

	if ((-1) = pipe(pipefd))
		perror("pipe");
	pid = fork();
	if (pid == 0)
	{
		if ((-1) == (fd1 = open(argv[1], O_RDONLY)))//argv[1]는 정확한 경로를 전달해 준다.
			perror("zsh");
		command1 = ft_split(argv[2], ' ');
		idx = 0;
		while (filepath[idx])
		{
			strcpy(filename1, filepath[idx]);
			strcat(filename1, "/");
			strcat(filename1, command1[0]);
			if (!access(filename1, F_OK))
				break;
			idx++;
		}
		if (!filepath[idx])
		{
			write(2, "zsh: command not found: ", 24);
			write(2, command1[0], ft_strlen(command1[0]));
			exit(127);
		}
		dup2(fd1, 0);// 0 -> fd1
		dup2(pipefd[1], 1);
		execve(filename1, command1, envp);
	}
	else
	{
		wait(&stat);
		if 
		dup2(pipefd[0], 0);
		close(pipefd[1]);
		command2 = ft_split(argv[3], ' ');
		idx = 0;
		while (filepath[idx])
		{
			strcpy(filename2, filepath[idx]);
			strcat(filename2, "/");
			strcat(filename2, command2[0]);
			if (!access(filename2, X_OK))
				break;
			idx++;
		}
		if (!filepath[idx])
		{
			write(2, "zsh: command not found: ", 24);
			write(2, command2[0], ft_strlen(command2[0]));
			exit(127);
		}
		char *outfile = malloc(sizeof(char) * (strlen(argv[argc - 1]) + 3));
		strcpy(outfile, "./");
		strcat(outfile, argv[argc - 1]);
		int fd_out = open(outfile, (O_RDWR | O_CREAT), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(fd_out, 1);
		execve(filename2, command2, envp);
	}
}