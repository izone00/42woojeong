/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:24:37 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/08 21:41:20 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_ex.h"

// uniquely 1 -> pipefd[out][w], pipefd[out][r] open in success
int	stdout_redir_pipe(int pipefd[2][2])
{
	int temp_out;
	int temp_in;

	if (pipe(pipefd[out]) < 0)
		return (0);
	//
	temp_out = dup(pipefd[out][w]);
	temp_in = dup(pipefd[out][r]);
	close(pipefd[out][w]);
	close(pipefd[out][r]);
	pipefd[out][w] = temp_out;
	pipefd[out][r] = temp_in;
	// 
	ft_putnbr_fd(pipefd[out][w], stdout_cpy);
	ft_putnbr_fd(pipefd[out][r], stdout_cpy);
	if (dup2(pipefd[out][w], 1) < 0)
	{
		close(pipefd[out][w]);
		close(pipefd[out][r]);
		return (0);
	}
	close(pipefd[out][w]);
	return (1);
}

int	make_exe_param(char ***cmd_argv, char **cmd_path, char *argv_i, char *path[])
{
	*cmd_argv = ft_split(argv_i, ' ');// malloc
	if (!cmd_argv)
		return (0);
	*cmd_path = get_cmd_path((*cmd_argv)[0], path); // malloc
	if (!cmd_path)
	{
		free(*cmd_argv);
		*cmd_argv = NULL;
		return (0);
	}
	return (1);
}

int	exe_cmd(char *cmd_path, char **cmd_argv, char *envp[])
{
	int	pid;
	
	pid = fork();
	if (pid < 0)
	{
		perror("zsh");
		return (0);
	}
	if (pid == 0) // child process
	{
		if (execve(cmd_path, cmd_argv, envp) < 0)
		{
			perror("zsh");
			//free_child();// child를 위한 free및 close 필요
			exit(1); 
		}
	}
	return (1);
}
// void	free_child()
// {

// }
// void	err_close_free(char *err, char *close, char *free)
// {

// }
int	exe_last_cmd(char *arg_file, char *cmd, char *path[], int pipefd[2][2], char *envp[])
{
	char	*file2 = get_file_path(arg_file); // malloc
	if (!file2)
	{
		perror("zsh");
		return (1);
	}
	if (access(file2, F_OK) == 0)
		unlink(file2);
	int fd2 = open(file2, (O_WRONLY | O_CREAT), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd2 < 0)
	{
		perror("zsh");
		//write(file2)???
		free(file2);
		return (0);
	}
	char **cmd_argv = ft_split(cmd, ' ');// malloc
	if (!cmd_argv)
	{
		perror("zsh");
		free(file2);
		close(fd2);
		return (1);
	}
	char *cmd_path = get_cmd_path(cmd_argv[0], path);
	if (!cmd_path)
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		// ft_putstr_fd(, 2);
		// malloc실패와 path 없음을 구분
		close(fd2);
		free(file2);
		free(cmd_argv);
		return (1);
	}
	dup2(fd2, 1);
	//if (dup fail)
	int pid = fork();
	if (pid < 0)
	{
		perror("zsh");
		close(fd2);
		free(file2);
		free(cmd_argv);
		free(cmd_path);
		return (0);
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, cmd_argv, envp) < 0)
		{
			perror("zsh");
			close(fd2);
			close(pipefd[out][w]);
			free(file2);
			free(cmd_path);
			free(cmd_argv);
			return (0);
		}
	}
	close(fd2);
	close(pipefd[out][w]);
	free(file2);
	free(cmd_path);
	free(cmd_argv);
	return (0);
}
int	exe_first_cmd(char *file, char *cmd, char *path[], int pipefd[2][2], char *envp[])
{
	char *file1 = get_file_path(file);// malloc
	if (!file1)
	{
		perror("zsh");
		return (1);
	}
	if (access(file1, R_OK) < 0)
	{
		perror("zsh");
		ft_putstr_fd(file, 2);
		free(file1);
		return (1);
	}
	int fd1 = open(file1, O_RDONLY);
	if (fd1 == -1)
	{
		perror("zsh");
		free(file1);
		return (1);
	}
	char **cmd_argv = ft_split(cmd, ' ');// malloc
	if (!cmd_argv)
	{
		perror("zsh");
		free(file1);
		close(fd1);
		return (1);
	}
	char *cmd_path = get_cmd_path(cmd_argv[0], path);
	if (!cmd_path)
	{
		ft_putstr_fd("zsh: command not found: ", 2);
		// ft_putstr_fd(arg_cmd, 2);
		close(fd1);
		free(file1);
		free(cmd_argv);
		return (1);
	}
	if (dup2(fd1, 0) < 0)
	{
		perror("zsh");
		close(fd1);
		free(file1);
		free(cmd_path);
		free(cmd_argv);
		return (1);
	}
	if (pipe(pipefd[out]) < 0)
	{
		perror("zsh");
		close(fd1);
		free(file1);
		free(cmd_path);
		free(cmd_argv);
		return (1);
	}
	if (dup2(pipefd[out][w], 1) < 0)
	{
		perror("zsh");
		close(fd1);
		close(pipefd[out][w]);
		free(file1);
		free(cmd_path);
		free(cmd_argv);
		return (0);
	}
	int pid = fork();
	if (pid < 0)
	{
		perror("zsh");
		close(fd1);
		close(pipefd[out][w]);
		free(file1);
		free(cmd_path);
		free(cmd_argv);
		return (0);
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, cmd_argv, envp) < 0)
		{
			perror("zsh");
			close(fd1);
			close(pipefd[out][w]);
			free(file1);
			free(cmd_path);
			free(cmd_argv);
			return (0);
		}
	}
	wait(NULL);
	close(fd1);
	close(pipefd[out][w]);
	free(file1);
	free(cmd_path);
	free(cmd_argv);
	return (0);
}

