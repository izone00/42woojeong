
#include "mini.h"

// 특수기호: '$', '<', '>', "<<", ">>", '|'

int stddout;

t_cmd_info *parse_cmd_line(char *line)
{
	//parse
	t_cmd_info *cmd_list;
	// cat -e << end | ls -l >> outfile

	// [ "cat -e", <, "infile", pipe, NULL ]
	cmd_list = malloc(sizeof(t_cmd_info) * 3);
	cmd_list[0].argv = strdup("cat -e");
	cmd_list[0].in_type = file;
	cmd_list[0].in_str = strdup("infile");
	cmd_list[0].out_type = pip;
	cmd_list[0].out_str = NULL;
	// [ "ls -l", pipe, NULL, >>, "outfile" ]
	cmd_list[1].argv = strdup("cat -e");
	cmd_list[1].in_type = pip;
	cmd_list[1].in_str = NULL;
	cmd_list[1].out_type = pip;
	cmd_list[1].out_str = NULL;
	// [ "ls -l", pipe, NULL, >>, "outfile" ]
	cmd_list[2].argv = strdup("ls -l");
	cmd_list[2].in_type = pip;
	cmd_list[2].in_str = NULL;
	cmd_list[2].out_type = file2;
	cmd_list[2].out_str = strdup("outfile");

	cmd_list[3].argv = NULL;
	return (cmd_list);
}

void check_in_type(t_cmd_info *cmd, int remain_pipe)
{
	if (cmd -> in_type == file)
	{
		int fd = open(cmd -> in_str, O_RDONLY);
		dup2(fd, 0);
		ft_putstr_fd("  ", stddout);
		ft_putnbr_fd(fd, stddout);
		if (fd != 0)
			close(fd);
	}
	else if (cmd -> in_type == pip)
	{
		dup2(remain_pipe, 0);
		if (remain_pipe != 0)
			close(remain_pipe);
	}
	else if (cmd -> in_type == here_doc)
	{
		// open_here_doc();
		printf("here");
	}
}

void check_out_type(t_cmd_info *cmd, int pipefd[2])
{
	if (cmd -> out_type == file)
	{
		int fd = open(cmd -> out_str, (O_RDWR | O_CREAT), \
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		dup2(fd, 1);
		if (fd != 1)
			close(fd);
	}
	else if (cmd -> out_type == pip)
	{
		pipe(pipefd);
		dup2(pipefd[1], 1);
		if (pipefd[1] != 1)
			close(pipefd[1]);
	}
	else if (cmd -> out_type == file2)
	{

		int fd = open(cmd ->out_str, (O_RDWR | O_CREAT), \
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		// 끝까지 read하기
		dup2(fd, 1);
		if (fd != 1)
			close(fd);
	}
	else if (cmd -> out_type == ft_stdout)
	{
		dup2(stddout, 1);
		if (stddout != 1)
			close(stddout);
	}
}

void exe(char *cmd_path, char **cmd_argv, char *envp[])
{
	int	pid;

	pid = fork();
	if (pid == 0)
		execve(cmd_path, cmd_argv, envp);
}

void exe_cmd(t_cmd_info *cmd_list, char **path, char **envp)
{
	int i = 0;
	int pipefd[2];
	char **cmd_argv;
	char *cmd_path;

	while (cmd_list[i].argv)
	{
		ft_putnbr_fd(i, stddout);
		check_in_type(cmd_list + i, pipefd[0]);
		check_out_type(cmd_list + i, pipefd);
		make_exe_param(&cmd_argv, &cmd_path, cmd_list[i].argv, path);
		exe(cmd_path, cmd_argv, envp);
		close(0);
		close(1);
		ft_putstr_fd("  ", stddout);
		ft_putnbr_fd(pipefd[0], stddout);
		ft_putnbr_fd(pipefd[1], stddout);
		ft_putstr_fd("\n", stddout);
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd_info *cmd_list;
	char *cmd_line;
	char **path;

	stddout = dup(1);
	path = get_path(envp);
	// while()
	// {
		cmd_line = readline("minishell $ ");
		add_history(cmd_line);// 자동으로 history동작 구현
		cmd_list = parse_cmd_line(cmd_line);
		exe_cmd(cmd_list, path, envp);
		free(cmd_line);
	// }
}


/*

*/