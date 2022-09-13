/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_first_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:52:23 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/13 18:54:30 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_ex.h"

int cmd_file_to_pipe(char *argv_i[], char *path[], int pipefd[2][2], char *envp[])
{
	char	**cmd_argv;
	char	*cmd_path;
	
	if (!stdout_redir_pipe(pipefd))// uniquely 1 -> pipefd[out][w], pipefd[out][r] open in success
		return (0);
	if (stdin_redir_infile(argv_i[0]))// uniquely 0 -> fd1 in success
	{
		if (make_exe_param(&cmd_argv, &cmd_path, argv_i[1], path)) // malloc
		{
			if (exe_cmd(cmd_path, cmd_argv, envp))// always parent process
				wait(NULL);
			free(cmd_path);
			free(cmd_argv);
		}
		close(0);
	}
	close(1);
	pipefd[in][r] = pipefd[out][r];
	return (1); // pipefd[in][r] is the only custom descriptor
}