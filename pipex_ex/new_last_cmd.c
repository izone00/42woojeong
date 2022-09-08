/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_last_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:54:55 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/08 21:42:01 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_ex.h"

int	short_exe_last_cmd(char *argv_i[], char *path[], int pipefd[2][2], char *envp[])
{
	char	**cmd_argv;
	char	*cmd_path;

	if (!stdout_to_outfile(argv_i[1]))// uniquely 1 -> fd2 in success
		return (0);
	if (stdin_redir_pipe(pipefd)) // uniquely 0 -> pipefd[in][r] in success, always pipefd[in][r] is closed
	{
		if (!make_exe_param(&cmd_argv, &cmd_path, argv_i[0], path)) // malloc
		{
			close(0);
			close(1);
			return (0); // there is no custom descriptor
		}
		if (exe_cmd(cmd_path, cmd_argv, envp)) // here is always parent process
			wait(NULL);
		close(0);
		free(cmd_path);
		free(cmd_argv);
	} // fd1을 만드는데 실패
	close(1);
	return (1);
}

int	stdout_to_outfile(char *filename)
{
	char	*file2;
	int	fd2;

	file2 = get_file_path(filename); // malloc
	if (!file2)
		return (0);
	if (!access(file2, F_OK))// 존재할때 에러는 잘 모르겟다
	{
		if (unlink(file2) < 0)
		{
			perror("zsh");
			free(file2);
			return (0);
		}
	}
	fd2 = open(file2, (O_WRONLY | O_CREAT), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd2 < 0)
	{
		perror("zsh");
		free(file2);
		return (0);
	}
	if (fd2 == 1 || fd2 == 0)
	{
		dup2(fd2, 100);
		close(fd2);
		fd2 = 100;
	}
	if (dup2(fd2, 1) < 0)
	{
		perror("zsh");
		close(fd2);
		free(file2);
		return (0);
	}
	close(fd2);
	free(file2);
	return (1);
}