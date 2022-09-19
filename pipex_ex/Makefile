# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/15 17:21:51 by woojeong          #+#    #+#              #
#    Updated: 2022/09/15 17:33:39 by woojeong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
SOURS = main.c pipe_to_file.c pipe_to_file_eof.c pipe_to_pipe.c\
		read_by_heredoc.c redir_pipe.c stdin_redir_infile.c\
		stdout_redir_outfile.c util.c get_path.c file_to_pipe.c\
		here_doc.c
NAME = pipex
LIB = ./libft_ex/libft.a


all:
			cd libft_ex
		##	cc ${CFLAGS} ${SOURS} ${LIB} -o ${NAME}

clean:
			rm -f ${OBJS} ${B_OBJS}

fclean:		clean
			rm -f ${NAME}

re:			
			@make fclean
			@make all

.PHONY:		all clean fclean re bonus
