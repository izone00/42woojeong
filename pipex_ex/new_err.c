/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:38:49 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/13 19:11:17 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_ex.h"
// stdin_redir_infile err
int	err_access(char **file1, char *filename)
{
	perror("zsh");
	ft_putstr_fd(filename, 2);
	free(*file1);
	return (0);
}

int	err_open(char **file1)
{
	perror("zsh");
	free(*file1);
	return (0);
}

int err_dup2(char **file1, int *fd1)
{
	perror("zsh");
	close(*fd1);
	free(*file1);
	return (0);
}

char	*err_malloc()
{
	perror("zsh");
	return (NULL);
}

char	*err_malloc_free(char **temp)
{
	perror("zsh");
	free(*temp);
	return (NULL);
}

int	err_malloc_close(int *fd)
{
	perror("zsh");
	close(*fd);
	return ()
}

char	*cmd_not_found(char *cmd)
{
	write(2, "zsh: command not found: ", 24);
	write(2, cmd, ft_strlen(cmd));
	return (NULL);
}
void	argc_err()
{
	write(2, "more argument", 13);
	exit(1);
}
// void	err_here_pipe(int pipefd[2][2])
// {
// 	perror("zsh");
// 	exit(1);
// }

// int	err_limiter_malloc()
// {
// 	perror("zsh");
// 	close(pipefd[in][w]);
// 	return (0);
// }

// int	err_putstr(char **p_limiter, int pipefd[2][2])
// {
// 	perror("zsh");
// 	close(pipefd[in][w]);
// 	free(*p_limiter);
// 	return (0);
// }