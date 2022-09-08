/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_first_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:52:23 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/08 20:33:42 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_ex.h"

int short_exe_first_cmd(char *argv_i[], char *path[], int pipefd[2][2], char *envp[])
{
	char	**cmd_argv;
	char	*cmd_path;
	
	if (!stdout_redir_pipe(pipefd))// uniquely 1 -> pipefd[out][w], pipefd[out][r] open in success
		return (0);
	if (stdin_redir_infile(argv_i[0]))// uniquely 0 -> fd1 in success
	{
		if (!make_exe_param(&cmd_argv, &cmd_path, argv_i[1], path)) // malloc
		{
			close(0);
			close(1);
			pipefd[in][r] = pipefd[out][r]; 
			return (0); // pipefd[in][r] is the only custom descriptor
		}
		if (exe_cmd(cmd_path, cmd_argv, envp))// always parent process
			wait(NULL);
		close(0);
		free(cmd_path);
		free(cmd_argv);
	}// fd1을 만드는데 실패
	close(1);
	pipefd[in][r] = pipefd[out][r];
	return (1); // pipefd[in][r] is the only custom descriptor
}

//return (0: redir fail, 1: redir 0 -> fd1 uniquely)
int	stdin_redir_infile(char *filename)
{
	char	*file1;
	int		fd1;

	file1 = get_file_path(filename);// malloc
	if (!file1)
		return (0);
	if (access(file1, R_OK) < 0)//없으면 경로 이후에 pipe를 만들어 다음 진행
	{
		perror("zsh");
		ft_putstr_fd(filename, 2);
		free(file1);
		return (0);
	}
	fd1 = open(file1, O_RDONLY);
	if (fd1 < 0)// open 실패시 
	{
		perror("zsh");
		free(file1);
		return (0);
	}
	if (dup2(fd1, 0) < 0)
	{
		perror("zsh");
		close(fd1);
		free(file1);
		return (0);
	}
	close(fd1);
	free(file1);
	return (1);
}