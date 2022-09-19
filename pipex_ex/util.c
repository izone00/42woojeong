/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 15:24:37 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/19 18:56:17 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

int	make_exe_param(char ***cmd_av, char **cmd_pa, char *argv_i, char *path[])
{
	*cmd_av = ft_split(argv_i, ' ');
	if (!*cmd_av)
	{
		perror("zsh");
		return (0);
	}
	if ((*cmd_av)[0][0] == '/' || (*cmd_av)[0][0] == '.')
		*cmd_pa = (*cmd_av)[0];
	else
		*cmd_pa = get_cmd_path((*cmd_av)[0], path);
	if (!*cmd_pa)
	{
		free(*cmd_av);
		*cmd_av = NULL;
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
	if (pid == 0)
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

char	*cmd_not_found(char *cmd)
{
	write(2, "zsh: command not found: ", 24);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	return (NULL);
}
