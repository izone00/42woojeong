#include "pipe_ex.h"

static int	err_access(char *file1, char *filename);
static int	err_open(char *file1);
static int err_dup2(char *file1, int fd1);

//return (0: redir fail, 1: redir 0 -> fd1 uniquely)
int	stdin_redir_infile(char *filename)
{
	char	*file1;
	int		fd1;

	file1 = get_file_path(filename);// malloc
	if (!file1)
		return (0);
	if (access(file1, R_OK) < 0)//없으면 경로 이후에 pipe를 만들어 다음 진행
		return (err_access(file1, filename));
	fd1 = open(file1, O_RDONLY);
	if (fd1 < 0)// open 실패시 
		err_open(file1);
	if (fd1 != 0)
	{
		if (dup2(fd1, 0) < 0)
			return (err_dup2(file1, fd1));
		close(fd1);
	}
	free(file1);
	return (1);
}

static int	err_access(char *file1, char *filename)
{
	perror("zsh");
	ft_putstr_fd(filename, 2);
	free(file1);
	return (0);
}

static int	err_open(char *file1)
{
	perror("zsh");
	free(file1);
	return (0);
}

static int err_dup2(char *file1, int fd1)
{
	perror("zsh");
	close(fd1);
	free(file1);
	return (0);
}