/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 21:03:10 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/06 21:19:51 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipe_ex.h"

int main(int argc, char *argv[], char *envp[])
{
	if (argc < 5) //인자 부족
	{exit(1);}

	char **path = get_path(envp);
	if (path == 0) // path찾는중 에러
	{exit(1);}

	int pipefd[2][2];
	int stdin_cpy = dup(0);
	int stdout_cpy = dup(1);
	if (exe_first_cmd(argv[1], argv[2], path, pipefd, envp))
		write(stdout_cpy, "[u]\n", 4);
	else
		write(stdout_cpy, "[d]\n", 4);
	int idx = 3;
	while (idx < argc - 2)
	{
		// exe_pipe_cmd();
		idx++;
	}
	dup2(pipefd[out][r], 0);
	exe_last_cmd(argv[argc - 1], argv[argc - 2], path, pipefd, envp);
}

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

//return (0: 다음 인풋을 pipe로, 1: 다음 인풋을 stdin???)
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