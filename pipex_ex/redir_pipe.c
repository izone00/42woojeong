/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 20:19:19 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/19 19:00:31 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	ft_pipe(int pipefd[2][2]);
static int	err(int pipefd[2][2]);
static int	err2(int pipefd[2][2]);

int	stdout_redir_pipe(int pipefd[2][2])
{
	if (ft_pipe(pipefd) < 0)
		return (0);
	if (dup2(pipefd[out][w], 1) < 0)
		return (err(pipefd));
	close(pipefd[out][w]);
	return (1);
}

int	stdin_redir_pipe(int pipefd[2][2])
{
	if (dup2(pipefd[in][r], 0) < 0)
		return (err2(pipefd));
	close(pipefd[in][r]);
	return (1);
}

static int	ft_pipe(int pipefd[2][2])
{
	int	fd1;
	int	fd2;

	if (pipe(pipefd[out]) < 0)
	{
		perror("zsh");
		write(2, "\n", 1);
		return (0);
	}
	fd1 = dup(pipefd[out][r]);
	fd2 = dup(pipefd[out][w]);
	if (fd1 < 0 || fd2 < 0)
		return (0);
	close(pipefd[out][w]);
	close(pipefd[out][r]);
	pipefd[out][r] = fd1;
	pipefd[out][w] = fd2;
	return (1);
}

static int	err(int pipefd[2][2])
{
	perror("zsh");
	write(2, "\n", 1);
	close(pipefd[out][w]);
	close(pipefd[out][r]);
	return (0);
}

static int	err2(int pipefd[2][2])
{
	perror("zsh");
	write(2, "\n", 1);
	close(pipefd[in][r]);
	return (0);
}
