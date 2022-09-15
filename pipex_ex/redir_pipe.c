/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 20:19:19 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/15 16:50:33 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_ex.h"

static int	ft_pipe(int pipefd[2][2]);
static int	err(int pipefd[2][2]);
static int	err2(int pipefd[2][2]);

// uniquely 1 -> pipefd[out][w], pipefd[out][r] open in success
int	stdout_redir_pipe(int pipefd[2][2])
{
	if (ft_pipe(pipefd) < 0)
		return (0);
	if (dup2(pipefd[out][w], 1) < 0)
		return (err(pipefd));
	close(pipefd[out][w]);
	return (1);
}

int stdin_redir_pipe(int pipefd[2][2])
{
	if (dup2(pipefd[in][r], 0) < 0)
		return (err2(pipefd));
	close(pipefd[in][r]);
	return (1);
}

static int	ft_pipe(int pipefd[2][2])
{
	if (pipe(pipefd[out]) < 0)
	{
		perror("zsh");
		return (0);
	}
	return (1);
}

static int	err(int pipefd[2][2])
{
	perror("zsh");
	close(pipefd[out][w]);
	close(pipefd[out][r]);
	return (0);	
}

static int	err2(int pipefd[2][2])
{
	perror("zsh");
	close(pipefd[in][r]);
	return (0);
}