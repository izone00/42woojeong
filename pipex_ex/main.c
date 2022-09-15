/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 21:03:10 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/15 16:59:06 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipe_ex.h"

static void	argc_err();
static void	err(char *path[]);

//exit 0 : out파일이 있다. 1 : out파일이 없다.
int main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2][2];
	char	**path;
	int		idx;

	if (argc < 5) //인자 부족
		argc_err();
	path = get_path(envp);
	if (path == 0) // path찾는중 에러
		exit(1);		
	stdout_cpy = dup(1);
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
	path_free(path);
	exit(0);
}

static void	argc_err()	
{
	write(2, "more argument", 13);
	exit(1);
}

static void	err(char *path[])
{
	path_free(path); // path free 함수가 필요하다.
	exit(1);
}