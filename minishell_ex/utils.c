#include "mini.h"

char	**get_path(char *envp[])
{
	int		idx;
	char	**path;

	idx = 0;
	while (envp[idx])
	{
		if (!ft_strncmp("PATH=", envp[idx], 5))
		{
			path = ft_split(envp[idx] + 5, ':');
			return (path);
		}
		idx++;
	}
	write(2, "no PATH", 7);
	return (NULL);
}

int	make_exe_param(char ***cmd_av, char **cmd_pa, char *argv_i, char *path[])
{
	*cmd_av = ft_split(argv_i, ' ');
	if ((*cmd_av)[0][0] == '/' || (*cmd_av)[0][0] == '.')
		*cmd_pa = ft_strdup((*cmd_av)[0]);
	else
		*cmd_pa = get_cmd_path((*cmd_av)[0], path);
	return (1);
}

char	*get_cmd_path(char *cmd, char *path[])
{
	int		idx;
	char	*temp;
	char	*cmd_path;

	temp = ft_strjoin("/", cmd);
	idx = 0;
	while (path[idx])
	{
		cmd_path = ft_strjoin(path[idx], temp);
		if (!access(cmd_path, F_OK))
			break ;
		free(cmd_path);
		idx++;
	}
	free(temp);
	return (cmd_path);
}