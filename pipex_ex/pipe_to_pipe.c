/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_to_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 18:54:32 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/27 18:24:44 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	pipe_to_pipe(char *argv_i[], char *path[], int pipefd[2][2], char *envp[])
{
	char	**cmd_argv;
	char	*cmd_path;

	if (!stdout_redir_pipe(pipefd))
		return (0);
	if (stdin_redir_pipe(pipefd))
	{
		if (make_exe_param(&cmd_argv, &cmd_path, argv_i[0], path))
		{
			if (exe_cmd(cmd_path, cmd_argv, envp))
				wait(NULL);
			free(cmd_path);
			array_free(cmd_argv);
		}
		close(0);
	}
	close(1);
	pipefd[in][r] = pipefd[out][r];
	return (1);
}
