/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:50:10 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/27 18:24:44 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static void	err(char *path[]);

int	here_doc(char *argv_i[], char *path[], int pipefd[2][2], char *envp[])
{
	if (!read_by_heredoc(argv_i[0], pipefd))
		err(path);
	if (!pipe_to_pipe(argv_i + 1, path, pipefd, envp))
		err(path);
	if (!pipe_to_file_eof(argv_i + 2, path, pipefd, envp))
		err(path);
	array_free(path);
	exit(0);
}

static void	err(char *path[])
{
	array_free(path);
	exit(1);
}
