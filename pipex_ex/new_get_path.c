/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_get_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:16:15 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/08 20:04:43 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipe_ex.h"

char	**get_path(char *envp[])
{
	int	idx;

	idx = 0;
	while (envp[idx])
	{
		if (!ft_strncmp("PATH=", envp[idx], 5))
			return (ft_split(envp[idx], ':'));
		idx++;
	}
	return (NULL);
}

char	*get_file_path(char *file)
{
	char	*path;

	if (file[0] =='/' && file[0] == '.')
	{
		path = ft_strdup(file);
		if (!path)
			perror("zsh");
		return (path);
	}
	path = ft_strjoin("./", file);
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
		return (NULL);
	idx = 0;
	while (path[idx])
	{
		cmd_path = ft_strjoin(path[idx], temp);
		if (!cmd_path)
		{
			free(temp);
			return (NULL);
		}
		if (!access(cmd_path, F_OK))
			break;
		free(cmd_path);
		idx++;
	}
	free(temp);
	if (!path[idx])
		return (NULL);
	return (cmd_path);
}