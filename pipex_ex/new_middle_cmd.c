/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_middle_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:54:32 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/08 20:32:32 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_ex.h"

int short_exe_middle_cmd(char *argv_i[], char *path[], int pipefd[2][2], char *envp[])
{
	char	**cmd_argv;
	char	*cmd_path;

	if (!stdout_redir_pipe(pipefd))// uniquely 1 -> pipefd[out][w], pipefd[out][r] open in success
		return (0);
	if (stdin_redir_pipe(pipefd))// uniquely 0 -> pipefd[in][r] in success, always pipefd[in][r] is closed 
	{
		if (!make_exe_param(&cmd_argv, &cmd_path, argv_i[0], path)) // malloc
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

int stdin_redir_pipe(int pipefd[2][2])
{
	if (dup2(pipefd[in][r], 0) < 0)
	{
		close(pipefd[in][r]);
		return (0);
	}
	close(pipefd[in][r]);
	return (1);
}