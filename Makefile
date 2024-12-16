# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoo <marvin@42.fr>                         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 17:41:52 by aoo               #+#    #+#              #
#    Updated: 2024/10/18 17:41:54 by aoo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mini-shell
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
#HEADER = -lreadline
RM = rm -rf

#LIBFT_DIR = ./Libft
#LIBFT = $(LIBFT_DIR)/libft.a

SRCS = func_test.c
OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} -lreadline

#${LIBFT}:
#	make -C ${LIBFT_DIR}

%.o: %.c
	${CC} ${CFLAGS} ${HEADER} -c $< -o $@

clean:
	#make clean -C ${LIBFT_DIR}
	${RM} ${OBJS}

fclean: clean
	#${RM} ${LIBFT}
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
