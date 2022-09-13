/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:50:10 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/13 19:02:52 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_ex.h"

int	here_doc(char *argv_i[], char **path[], int pipefd[2][2], char *envp[])
{
	// short_exe_first_cmd(argv_i, path, pipefd, envp);
	pipefd[in][r] = 0;
	if (!read_by_heredoc(argv_i[0], pipefd))
	{
		free(*path);
		exit(0);
	}
	if (pipefd[in][r])
	{
		short_exe_middle_cmd(argv_i + 1, *path, pipefd, envp);
	}
	heredoc_last_cmd(argv_i + 2, path, pipefd, envp);// success
	exit(0);
}