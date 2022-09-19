/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdout_redir_outfile.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:31:20 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/19 18:59:59 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	err_unlink(char *file2);
static int	err_open(char *file2);
static int	err_dup2(char *file2, int fd2);

int	stdout_redir_outfile(char *filename, int is_heredoc)
{
	char	*file2;
	int		fd2;

	file2 = get_file_path(filename);
	if (!file2)
		return (0);
	if (!access(file2, F_OK) && !is_heredoc)
	{
		if (unlink(file2) < 0)
			return (err_unlink(file2));
	}
	fd2 = open(file2, (O_RDWR | O_CREAT), \
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd2 < 0)
		return (err_open(file2));
	if (fd2 != 1)
	{
		if (dup2(fd2, 1) < 0)
			return (err_dup2(file2, fd2));
		close(fd2);
	}
	free(file2);
	return (1);
}

static int	err_unlink(char *file2)
{
	perror("zsh");
	write(2, "\n", 1);
	free(file2);
	return (0);
}

static int	err_open(char *file2)
{
	perror("zsh");
	write(2, "\n", 1);
	free(file2);
	return (0);
}

static int	err_dup2(char *file2, int fd2)
{
	perror("zsh");
	write(2, "\n", 1);
	close(fd2);
	free(file2);
	return (0);
}
