/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:44:36 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/27 18:24:44 by woojeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_H
# define FT_PIPEX_H
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>

enum e_pipe_num {
	r = 0,
	out = 0,
	w = 1,
	in = 1
};
char	*get_next_line(int fd);
int		ft_putstr_fd(char *str, int fd);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *str);
int		ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *str1);
int		file_to_pipe(char *av[], char *path[], int pipefd[2][2], char *envp[]);
char	**get_path(char *envp[]);
char	*get_file_path(char *file);
char	*get_cmd_path(char *cmd, char *path[]);
void	array_free(char *path[]);
int		here_doc(char *argv_i[], char *path[], int pipefd[2][2], char *envp[]);
int		read_by_heredoc(char *limiter, int pipefd[2][2]);
int		make_exe_param(char ***av, char **pa, char *argv_i, char *path[]);
int		exe_cmd(char *cmd_path, char **cmd_argv, char *envp[]);
int		pipe_to_file(char *av[], char *path[], int pipefd[2][2], char *envp[]);
int		pipe_to_pipe(char *av[], char *path[], int pipefd[2][2], char *envp[]);
int		stdout_redir_pipe(int pipefd[2][2]);
int		stdin_redir_infile(char *filename);
int		stdout_redir_outfile(char *filename, int is_heredoc);
int		stdin_redir_pipe(int pipefd[2][2]);
int		pipe_to_file_eof(char *av[], char *path[], int fd[2][2], char *envp[]);
char	*cmd_not_found(char *cmd);
#endif
