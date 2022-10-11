# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: woojeong <woojeong@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/15 17:21:51 by woojeong          #+#    #+#              #
#    Updated: 2022/10/11 17:28:06 by woojeong         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAG = -lmlx -framework OpenGL -framework AppKit 
SOURS = draw_img.c event.c get_img_scale.c get_map.c main.c\
		translate.c turn.c turn_event.c util.c zoom.c get_map_utils.c\
		draw_img_utils.c
OBJS = ${SOURS:.c=.o}
NAME = fdf
LIB = ./libft_ex/libft.a

all:		${NAME}

${NAME}:	${OBJS}	${LIB}
			cc  ${FLAG} ${SOURS} ${LIB} -o ${NAME}
${LIB}:
			make -C "libft_ex" -f makefile

bonus:
			@make all

clean:
			rm -f ${OBJS}
			make fclean -C "libft_ex" -f makefile

fclean:		clean
			rm -f ${NAME}

re:			
			@make fclean
			@make all

.PHONY:		all clean fclean re bonus
