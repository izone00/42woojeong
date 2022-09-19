/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin_redir_infile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:32:30 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/19 19:07:14 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	err_access(char *file1, char *filename);
static int	err_open(char *file1);
static int	err_dup2(char *file1, int fd1);

int	stdin_redir_infile(char *filename)
{
	char	*file1;
	int		fd1;

	file1 = get_file_path(filename);
	if (!file1)
		return (0);
	if (access(file1, R_OK) < 0)
		return (err_access(file1, filename));
	fd1 = open(file1, O_RDONLY);
	if (fd1 < 0)
		err_open(file1);
	if (fd1 != 0)
	{
		if (dup2(fd1, 0) < 0)
			return (err_dup2(file1, fd1));
		close(fd1);
	}
	free(file1);
	return (1);
}

static int	err_access(char *file1, char *filename)
{
	char	*err_str;

	err_str = ft_strjoin("zsh: ", filename);
	if (!err_str)
	{
		free(file1);
		return (0);
	}
	perror(err_str);
	free(err_str);
	free(file1);
	return (0);
}

static int	err_open(char *file1)
{
	perror("zsh");
	write(2, "\n", 1);
	free(file1);
	return (0);
}

static int	err_dup2(char *file1, int fd1)
{
	perror("zsh");
	write(2, "\n", 1);
	close(fd1);
	free(file1);
	return (0);
}
