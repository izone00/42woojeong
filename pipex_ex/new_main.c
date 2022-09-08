/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 21:03:10 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/08 20:41:58 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipe_ex.h"

int main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2][2];
	char	**path;

	if (argc < 5) //인자 부족
	{exit(1);}
	path = get_path(envp);
	if (path == 0) // path찾는중 에러
	{exit(1);}
	// int stdin_cpy = dup(0);
	// int stdout_cpy = dup(1);
	if (!short_exe_first_cmd(argv + 1, path, pipefd, envp))
	{
		free(path);
		exit(1);
	}

	int idx = 3;
	while (idx < argc - 2)
	{
		short_exe_middle_cmd(argv + idx, path, pipefd, envp);
		idx++;
	}
	short_exe_last_cmd(argv + argc - 2, path, pipefd, envp);
}

// file1이 없거나 권한이 없으면 다음 cmd로
//systemcall 실패 = exit(1);