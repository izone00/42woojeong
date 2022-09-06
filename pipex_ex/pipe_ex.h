/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_ex.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 21:03:28 by woojeong          #+#    #+#             */
/*   Updated: 2022/09/06 21:05:43 by woojeong         ###   ########.fr       */
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
typedef struct s_pipe{
	int	flag;
	int pipefd[2][2];
} t_pipe;

char	**ft_split(char const *s, char c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_strlen(const char *str);
int ft_putstr_fd(char *s, int fd);
char	**get_path(char *envp[]);
char	*get_file_path(char *file);
char	*get_cmd_path(char *cmd, char *path[]);
int	exe_first_cmd(char *file, char *cmd, char *path[], int pipefd[2][2], char *envp[]);
int	exe_last_cmd(char *arg_file, char *cmd, char *path[], int pipefd[2][2], char *envp[]);
int	convert_pipe(int pipefd[2][2]);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *str1);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

