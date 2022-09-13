/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_ex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 21:03:28 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/13 19:01:15 by woojeong         ###   ########.fr       */
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
int stdout_cpy; ////////////
void	here_doc(char *argv_i[], char **path[], int pipefd[2][2], char *envp[]); //////////
int	heredoc_last_cmd(char *argv_i[], char *path[], int pipefd[2][2], char *envp[]);/////////////
int offset_eof();////
char	*get_next_line(int fd);
int	read_by_heredoc(char *limiter, int pipefd[2][2]);
void	argc_err();
int	err_access(char **file1, char *filename);
int	err_open(char **file1);
int err_dup2(char **file1, int *fd1);
int err_malloc();
int err_malloc_free(char **temp);
int	cmd_not_found(char *cmd);
//libft
void	ft_putnbr_fd(int n, int fd);
int		ft_putstr_fd(char *str, int fd);
char	**ft_split(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_strlen(const char *str);
int ft_putstr_fd(char *s, int fd);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *str1);
//main
int	cmd_file_to_pipe(char *argv_i[], char *path[], int pipefd[2][2], char *envp[]);
int	short_exe_middle_cmd(char *argv_i[], char *path[], int pipefd[2][2], char *envp[]);
int	short_exe_last_cmd(char *argv_i[], char *path[], int pipefd[2][2], char *envp[]);
// path
char	**get_path(char *envp[]);
char	*get_file_path(char *file);
char	*get_cmd_path(char *cmd, char *path[]);
//util
int	stdout_redir_pipe(int pipefd[2][2]);
int	make_exe_param(char ***cmd_argv, char **cmd_path, char *argv_i, char *path[]);
int	exe_cmd(char *cmd_path, char **cmd_argv, char *envp[]);
int	stdin_redir_infile(char *filename);
int stdin_redir_pipe(int pipefd[2][2]);
int	stdout_redir_outfile(char *filename, int start_eof);
