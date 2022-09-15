/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:24:37 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/15 16:43:59 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_ex.h"

int	make_exe_param(char ***cmd_argv, char **cmd_path, char *argv_i, char *path[])
{
	*cmd_argv = ft_split(argv_i, ' ');// malloc
	if (!*cmd_argv)
	{
		perror("zsh");
		return (0);
	}
	*cmd_path = get_cmd_path((*cmd_argv)[0], path); // malloc
	if (!*cmd_path)
	{
		free(*cmd_argv);
		*cmd_argv = NULL;
		return (0);
	}
	return (1);
}

int	exe_cmd(char *cmd_path, char **cmd_argv, char *envp[])
{
	int	pid;
	
	pid = fork();
	if (pid < 0)
	{
		perror("zsh");
		return (0);
	}
	if (pid == 0) // child process
	{
		if (execve(cmd_path, cmd_argv, envp) < 0)
		{
			perror("zsh");
			//free_child();// child를 위한 free및 close 필요
			exit(1); 
		}
	}
	return (1);
}

void	path_free(char *path[])
{
	int	idx;

	idx = 0;
	while (path[idx])
	{
		free(path[idx]);
		idx++;
	}
	free(path);
}