/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 21:03:10 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/27 18:25:31 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static void	argc_err(void);
static void	err(char *path[]);

int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2][2];
	char	**path;
	int		idx;

	if (argc < 5 || (!ft_strncmp(argv[1], "here_doc", 9) && argc < 6))
		argc_err();
	path = get_path(envp);
	if (path == 0)
		exit(1);
	if (!ft_strncmp(argv[1], "here_doc", 9))
		here_doc(argv + 2, path, pipefd, envp);
	if (!file_to_pipe(argv + 1, path, pipefd, envp))
		err(path);
	idx = 3;
	while (idx < argc - 2)
	{
		if (!pipe_to_pipe(argv + idx, path, pipefd, envp))
			err(path);
		idx++;
	}
	if (!pipe_to_file(argv + argc - 2, path, pipefd, envp))
		err(path);
	array_free(path);
	exit(0);
}

static void	argc_err(void)
{
	write(2, "more argument", 13);
	exit(1);
}

static void	err(char *path[])
{
	array_free(path);
	exit(1);
}
