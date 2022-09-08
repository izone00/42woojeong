/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_ex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 21:03:28 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/08 20:31:50 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //perror
#include <string.h> //strerror
#include <unistd.h> //access
#include <sys/wait.h> //wait
#include <stdlib.h> //molloc
#include <fcntl.h> // open option
enum pipe_num {
	r = 0,
	out = 0,
	w = 1,
	in = 1
};
//libft
char	**ft_split(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_strlen(const char *str);
int ft_putstr_fd(char *s, int fd);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *str1);
//main
int	short_exe_first_cmd(char *argv_i[], char *path[], int pipefd[2][2], char *envp[]);
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
int	stdout_to_outfile(char *filename);
