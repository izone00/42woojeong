/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_by_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:25:39 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/15 19:11:25 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_ex.h"

static int	err(int fd);
static int	err2(char *limit, int fd);
static int	err3(char *limit, char *temp, int fd);
static int	read_until_limiter(char *limiter, int pipefd[2][2]);

int	read_by_heredoc(char *limiter, int pipefd[2][2])
{
	if (pipe(pipefd[in]) < 0)
		return (0);
	limiter = ft_strjoin(limiter, "\n"); //malloc
	if (!limiter)
		return (err(pipefd[in][w]));
	if (read_until_limiter(limiter, pipefd))
		return (1);
	close(pipefd[in][w]);
	return (1);
}

static int	read_until_limiter(char *limiter, int pipefd[2][2])
{
	char	*line;

	if (ft_putstr_fd("pipe heredoc> ", 1) < 0)
		return (err2(limiter, pipefd[in][w]));
	line = get_next_line(0);
	while (line != NULL)
	{
		if (!strncmp(line, limiter, ft_strlen(limiter)))
			break;
		if (ft_putstr_fd(line, pipefd[in][w]) < 0)
			return (err3(limiter, line, pipefd[in][w]));
		free(line);
		if (ft_putstr_fd("pipe heredoc> ", 1) < 0)
			return (err2(limiter, pipefd[in][w]));
		line = get_next_line(0);
	}
	if (!line)
		free(line);
	return (1);
}

static int	err(int fd)
{
	perror("zsh");
	write(2, "\n", 1);
	close(fd);
	return (1);
}

static int	err2(char *limit, int fd)
{
	perror("zsh");
	write(2, "\n", 1);
	close(fd);
	free(limit);
	return (0);
}

static int	err3(char *limit, char *line, int fd)
{
	perror("zsh");
	write(2, "\n", 1);
	close(fd);
	free(limit);
	free(line);
	return (0);
}