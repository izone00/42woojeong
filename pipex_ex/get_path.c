/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:16:15 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/15 19:11:44 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipe_ex.h"

static char	*err();
static char	*err2(char *temp);
static char	*cmd_not_found(char *cmd);

char	**get_path(char *envp[])
{
	int		idx;
	char	**path;

	idx = 0;
	while (envp[idx])
	{
		if (!ft_strncmp("PATH=", envp[idx], 5))
		{
			path = ft_split(envp[idx], ':');
			if (!path)
				perror("zsh");
			return (path);
		}
		idx++;
	}
	write(2, "no PATH", 7);
	return (NULL);
}

char	*get_file_path(char *file)
{
	char	*path;

	if (file[0] =='/' && file[0] == '.')
	{
		path = ft_strdup(file); // malloc
		if (!path)
			perror("zsh");
		return (path);
	}
	path = ft_strjoin("./", file); // malloc
	if (!path)
		perror("zsh");
	return (path);
}

char	*get_cmd_path(char *cmd, char *path[])
{
	int		idx;
	char	*temp;
	char	*cmd_path;

	temp = ft_strjoin("/", cmd);
	if (!temp)
		return (err());
	idx = 0;
	while (path[idx])
	{
		cmd_path = ft_strjoin(path[idx], temp);
		if (!cmd_path)
			return (err2(temp));
		if (!access(cmd_path, F_OK))
			break;
		free(cmd_path);
		idx++;
	}
	free(temp);
	if (!path[idx])
		return (cmd_not_found(cmd));
	return (cmd_path);
}

static char	*err()
{
	perror("zsh");
	write(2, "\n", 1);
	return (NULL);
}

static char	*err2(char *temp)
{
	perror("zsh");
	write(2, "\n", 1);
	free(temp);
	return (NULL);
}

static char	*cmd_not_found(char *cmd)
{
	write(2, "zsh: command not found: ", 24);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	return (NULL);
}