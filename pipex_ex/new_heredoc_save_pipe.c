/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_heredoc_save_pipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:25:39 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/13 20:51:51 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_ex.h"

int	err(int *fd);
int	err2(char **limit, int *fd);
int	err3(char **limit. char **temp, int *fd);

int	read_by_heredoc(char *limiter, int pipefd[2][2])
{
	char	*temp;

	if (pipe(pipefd[in]) < 0)
		return (0);
	limiter = ft_strjoin(limiter, "\n"); //malloc
	if (!limiter)
		return (err(&(pipefd[in][w]));
	if (ft_putstr_fd("pipe heredoc> ", 1) < 0)
		return (err2(&limiter, &(pipefd[in][w])));
	temp = get_next_line(0);
	while (temp != NULL)
	{
		if (!strncmp(temp, limiter, ft_strlen(limiter)))
			break;
		if (ft_putstr_fd(temp, pipefd[in][w]) < 0)
			return (err3(&limiter, &temp, &(pipefd[in][w])));
		free(temp);
		if (ft_putstr_fd("pipe heredoc> ", 1) < 0)
			return (err2(&limiter, &(pipefd[in][w])));
		temp = get_next_line(0);
	}
	close(pipefd[in][w]);
	if (!temp)
		free(temp);
	return (1);
}

static int	err(int *fd)
{
	perror("zsh");
	close(*fd);
	return ()
}

static int	err2(char **limit, int *fd)
{
	perror("zsh");
	close(*fd);
	free(*limit);
	return (0);
}

static int	err3(char **limit. char **temp, int *fd)
{
	perror("zsh");
	close(*fd);
	free(*limit);
	free(*temp);
	return (0);
}