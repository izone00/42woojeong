# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 20:46:01 by woojeong          #+#    #+#              #
#    Updated: 2022/09/27 17:55:16 by woojeong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
SOURS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
		ft_isdigit.c ft_isprint.c ft_tolower.c ft_memchr.c ft_memcmp.c \
		ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c \
		ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
		ft_toupper.c ft_strdup.c ft_calloc.c ft_substr.c ft_strjoin.c\
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c\
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
		get_next_line.c get_next_line_utils.c
B_SOURS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
		  ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
NAME = libft.a
OBJS = ${SOURS:.c=.o}
B_OBJS = ${B_SOURS:.c=.o}
ifdef BONUS_SIGN
	OBJS_FILES = ${OBJS} ${B_OBJS}
else
	OBJS_FILES = ${OBJS}
endif
all: 		${NAME}

${NAME}:	${OBJS_FILES}
			ar rc ${NAME} ${OBJS_FILES}
bonus:
			make BONUS_SIGN=1 all

clean:
			rm -f ${OBJS} ${B_OBJS}

fclean:		clean
			rm -f ${NAME}

re:			
			@make fclean
			@make all

.PHONY:		all clean fclean re bonus
