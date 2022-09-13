/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 20:19:19 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/13 20:22:14 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe_ex.h"

// uniquely 1 -> pipefd[out][w], pipefd[out][r] open in success
int	stdout_redir_pipe(int pipefd[2][2])
{
	if (pipe(pipefd[out]) < 0)
	{
		perror("zsh");
		return (0);
	}
	if (dup2(pipefd[out][w], 1) < 0)
	{
		perror("zsh");
		close(pipefd[out][w]);
		close(pipefd[out][r]);
		return (0);
	}
	close(pipefd[out][w]);
	return (1);
}

//return (0: redir fail, 1: redir 0 -> fd1 uniquely)
int	stdin_redir_infile(char *filename)
{
	char	*file1;
	int		fd1;

	file1 = get_file_path(filename);// malloc
	if (!file1)
		return (0);
	if (access(file1, R_OK) < 0)//없으면 경로 이후에 pipe를 만들어 다음 진행
		return (err_access(&file1, filename));
	fd1 = open(file1, O_RDONLY);
	if (fd1 < 0)// open 실패시 
		err_open(&file1);
	if (dup2(fd1, 0) < 0)
		return (err_dup2(&file1, &fd1));
	close(fd1);
	free(file1);
	return (1);
}

int stdin_redir_pipe(int pipefd[2][2])
{
	if (dup2(pipefd[in][r], 0) < 0)
	{
		close(pipefd[in][r]);
		return (0);
	}
	close(pipefd[in][r]);
	return (1);
}

int	stdout_redir_outfile(char *filename, int start_eof)
{
	char	*file2;
	int	fd2;

	file2 = get_file_path(filename); // malloc
	if (!file2)
		return (0);
	if (!access(file2, F_OK) && !start_eof)// 존재할때 에러는 잘 모르겟다
	{
		if (unlink(file2) < 0)
		{
			perror("zsh");
			free(file2);
			return (0);
		}
	}
	fd2 = open(file2, (O_RDWR | O_CREAT), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd2 < 0)
	{
		perror("zsh");
		free(file2);
		return (0);
	}
	if (fd2 == 1 || fd2 == 0)
	{
		dup2(fd2, 100);
		close(fd2);
		fd2 = 100;
	}
	if (dup2(fd2, 1) < 0)
	{
		perror("zsh");
		close(fd2);
		free(file2);
		return (0);
	}
	close(fd2);
	free(file2);
	return (1);
}