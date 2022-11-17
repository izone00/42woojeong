#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
#include "libft.h"
#include "ft_printf.h"


#define file 1
#define pip 2
#define here_doc 3
#define file2 4
#define ft_stdout 5



typedef struct s_cmd_info {
	char	*argv;
	int	in_type;
	char	*in_str;
	int	out_type;
	char	*out_str;
} t_cmd_info;

char	**get_path(char *envp[]);
int	make_exe_param(char ***cmd_av, char **cmd_pa, char *argv_i, char *path[]);
char	*get_cmd_path(char *cmd, char *path[]);