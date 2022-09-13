/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_heredoc_last_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:43:46 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/13 20:51:29 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_ex.h"

int	heredoc_last_cmd(char *argv_i[], char *path[], int pipefd[2][2], char *envp[])
{
	char	**cmd_argv;
	char	*cmd_path;

	if (!stdout_redir_outfile(argv_i[1], 1) || !offset_eof())// uniquely 1 -> fd2 in success
	{
		close(pipefd[in][r]);
		return (0);
	}
	if (stdin_redir_pipe(pipefd)) // uniquely 0 -> pipefd[in][r] in success, always pipefd[in][r] is closed
	{
		if (make_exe_param(&cmd_argv, &cmd_path, argv_i[0], path)) // malloc
		{
			if (exe_cmd(cmd_path, cmd_argv, envp)) // here is always parent process
				wait(NULL);
			free(cmd_path);
			free(cmd_argv);
		}
		close(0);
	}
	close(1);
	return (1);// there is no custom descriptor
}

int offset_eof()
{
	char	buff[10];
	int		read_len;
	
	while (0 < (read_len = read(1, buff, BUFFER_SIZE)))
		;
	if (read_len < 0)
		return (0);
	return (1);
}
