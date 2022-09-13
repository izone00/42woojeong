/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 21:03:10 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/13 20:49:06 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipe_ex.h"
//exit 0 : out파일이 있다. 1 : out파일이 없다.
int main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2][2];
	char	**path;

	if (argc < 5) //인자 부족
		argc_err();
	path = get_path(envp);
	if (path == 0) // path찾는중 에러
		exit(1);		
	stdout_cpy = dup(1);
	if (!ft_strncmp(argv[1], "here_doc", 9))
		here_doc(argv + 2, &path, pipefd, envp)
	if (!file_cmd_pipe(argv + 1, path, pipefd, envp))
		err(&path);
	int idx = 3;
	while (idx < argc - 2)
	{
		if (!pipe_cmd_pipe(argv + idx, path, pipefd, envp))
			err(&path);
		idx++;
	}
	if (!pipe_cmd_file(argv + argc - 2, path, pipefd, envp))
		err(&path);
	exit(0);
}

static void	err(char **path[])
{
	free(*path); // path free 함수가 필요하다.
	exit(1);
}