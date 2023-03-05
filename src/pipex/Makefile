# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vde-prad <vde-prad@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 11:02:01 by vde-prad          #+#    #+#              #
#    Updated: 2023/03/05 13:21:46 by vde-prad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= 	pipex.c \
		  	utils/setdata.c \
			utils/parserpath.c

OBJS	= ${SRCS:.c=.o}
NAME	= pipex
LIBRARY = ../../includes/libft_plus/libft.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

################# RULES #####################

all: lib comp
	
lib:
	@echo "\nCOMPILING LIBFT"
	@${MAKE} -C ../../includes/libft_plus

comp: ${NAME}

$(NAME): ${OBJS}
	@echo "\nCOMPILING PIPEX"
	@${CC} ${CFLAGS} ${OBJS} ${LIBRARY} -o ${NAME}

clean:
	@echo "LIMPIANDO"
	@${MAKE} -C ../../includes/libft_plus clean
	@${RM} ${OBJS}

fclean: clean
	@${MAKE} -C ../../includes/libft_plus fclean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
