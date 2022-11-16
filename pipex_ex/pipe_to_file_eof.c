/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_to_file_eof.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:43:46 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/27 18:24:44 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	offset_to_eof(void);

int	pipe_to_file_eof(char *av_i[], char *path[], int pipefd[2][2], char *envp[])
{
	char	**cmd_argv;
	char	*cmd_path;

	if (!stdout_redir_outfile(av_i[1], 1) || !offset_to_eof())
	{
		close(pipefd[in][r]);
		return (0);
	}
	if (stdin_redir_pipe(pipefd))
	{
		if (make_exe_param(&cmd_argv, &cmd_path, av_i[0], path))
		{
			if (exe_cmd(cmd_path, cmd_argv, envp))
				wait(NULL);
			free(cmd_path);
			array_free(cmd_argv);
		}
		close(0);
	}
	close(1);
	return (1);
}

static int	offset_to_eof(void)
{
	char	buff[10];
	int		read_len;

	read_len = 1;
	while (0 < read_len)
		read_len = read(1, buff, 10);
	if (read_len < 0)
	{
		perror("zsh");
		return (0);
	}
	return (1);
}
