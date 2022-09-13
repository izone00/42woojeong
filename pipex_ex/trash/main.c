#include <stdio.h>//perror
#include <string.h>//strerror
#include <unistd.h>//access

#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
char	**ft_split(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_strlen(const char *str);

int	main()
{
	//fork
	//
}
int main(int argc, char *argv[], char *envp[])//env는 null terminate되있다.
{
	pid_t	*pid;
	char	**cmd1;
	char	**cmd2;
	char	**fpath;
	char	fname1[30];
	char	fname2[30];
	int		stat;
	int		inpipe[2];
	int		outpipe[2];
	int		fd1;
	int		fd2;
	int		idx;
//경로를 통한 실행이랑 
	if (argc < 5)
	{
		write(1, "more argument", 13);
		exit(1);
	}
	pid = (pid_t *)malloc(sizeof(pid_t) * (argc - 4));
	if (!pid)
		exit(1);
	//command경로 fpath에 저장
	idx = 0;
	fpath = NULL;
	while (envp[idx])
	{
		if (!ft_strncmp("PATH=", envp[idx], 5))
			fpath = ft_split(envp[idx], ':');
		idx++;
	}
	if (!fpath)
		perror("no PATH"); // PATH경로가 없을때
	//file1으로부터 데이터 가져오기
	if ((-1) = pipe(outpipe))
		perror("bash");
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		if ((-1) == (fd1 = open(argv[1], O_RDONLY)))//argv[1]는 정확한 경로를 전달해 준다.
			perror("zsh");
		cmd1 = ft_split(argv[2], ' ');
		search_cmd(fpath, fname1, cmd1[0]);
		if(dup2(fd1, 0) < 0)
			error_print();// 0 -> fd1
		close(fd1);
		dup2(pipefd[1], 1);
		execve(fname1, cmd1, envp);
	}
	while()
	{
		//wait
		//input : inpipe[0]
		//output : outpipe[1]
		//위 설정으로 fork를 실행해 outpipe[0]에 데이터 넣기
		//inpipe를 닫고 다시 열어 outpipe[0]에 데이터를 inpipe[1]에 넣고 outpipe닫고 다시 열기
	}
	//데이터를 file2에 넣기
	if()
	{
		wait(&stat);
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		cmd2 = ft_split(argv[3], ' ');
		idx = 0;
		while (fpath[idx])
		{
			strcpy(fname2, fpath[idx]);
			strcat(fname2, "/");
			strcat(fname2, cmd2[0]);
			if (!access(fname2, X_OK))
				break;
			idx++;
		}
		if (!fpath[idx])
		{
			write(2, "zsh: command not found: ", 24);
			write(2, cmd2[0], ft_strlen(cmd2[0]));
			exit(127);
		}
		char *outfile = malloc(sizeof(char) * (strlen(argv[argc - 1]) + 3));
		strcpy(outfile, "./");
		strcat(outfile, argv[argc - 1]);
		int fd_out = open(outfile, (O_RDWR | O_CREAT), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(fd_out, 1);
		execve(fname2, cmd2, envp);
	}
}

void	search_cmd(char **fpath, char *fname, char cmd)
{
	int	idx;

	idx = 0;
	while (fpath[idx])
	{
		strcpy(fname, fpath[idx]);
		strcat(fname, "/");
		strcat(fname, cmd);
		if (!access(fname, F_OK))
			break;
		idx++;
	}
	if (!fpath[idx])
	{
		write(2, "zsh: command not found: ", 24);
		write(2, cmd, ft_strlen(cmd));
		exit(127);//???????????
	}
}