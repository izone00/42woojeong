/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_ex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 21:03:28 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/15 18:49:31 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //perror
#include <string.h> //strerror
#include <unistd.h> //access
#include <sys/wait.h> //wait
#include <stdlib.h> //molloc
#include <fcntl.h> // open option

#define BUFFER_SIZE 10

enum pipe_num {
	r = 0,
	out = 0,
	w = 1,
	in = 1
};
//temp
int stdout_cpy;
void	ft_putnbr_fd(int n, int fd);

//gnl
char	*get_next_line(int fd);
//libft
int		ft_putstr_fd(char *str, int fd);
char	**ft_split(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_strlen(const char *str);
int ft_putstr_fd(char *s, int fd);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *str1);
//file_to_pipe
int file_to_pipe(char *argv_i[], char *path[], int pipefd[2][2], char *envp[]);
// get_path
char	**get_path(char *envp[]);
char	*get_file_path(char *file);
char	*get_cmd_path(char *cmd, char *path[]);
void	path_free(char *path[]);
// here_doc
int	here_doc(char *argv_i[], char *path[], int pipefd[2][2], char *envp[]);
// read_by_heredoc
int	read_by_heredoc(char *limiter, int pipefd[2][2]);
//util
int	make_exe_param(char ***cmd_argv, char **cmd_path, char *argv_i, char *path[]);
int	exe_cmd(char *cmd_path, char **cmd_argv, char *envp[]);
void	path_free(char *path[]);
//pipe_to_file
int	pipe_to_file(char *argv_i[], char *path[], int pipefd[2][2], char *envp[]);
//pipt_to_pipe
int pipe_to_pipe(char *argv_i[], char *path[], int pipefd[2][2], char *envp[]);
//redir_pipe
int	stdout_redir_pipe(int pipefd[2][2]);
int stdin_redir_pipe(int pipefd[2][2]);
//stdin_redir_infile
int	stdin_redir_infile(char *filename);
//stdout_redir_outfile
int	stdout_redir_outfile(char *filename, int is_heredoc);
//pipe_to_file_eof
int	pipe_to_file_eof(char *argv_i[], char *path[], int pipefd[2][2], char *envp[]);