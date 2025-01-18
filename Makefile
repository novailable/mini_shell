# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 17:41:52 by aoo               #+#    #+#              #
#    Updated: 2025/01/18 18:13:41 by aoo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mini_shell
CC = cc
CFLAGS = -g #-Wall -Wextra -Werror
HEADER = -I Libft
RM = rm -rf

LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = mini_shell.c utils.c execution.c first_processing.c\
		built_in/export.c built_in/env.c built_in/unset.c built_in/pwd.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}
	@echo "${NAME} created."

${NAME}: ${OBJS} ${LIBFT}
	@echo "${NAME} compiling..."
	@${CC} ${CFLAGS} ${HEADER} -lft -L${LIBFT_DIR} ${OBJS} ${LIBFT} -lreadline -o ${NAME}

${LIBFT}:
	@make -C ${LIBFT_DIR}

%.o: %.c
	@${CC} ${CFLAGS} ${HEADER} -c $< -o $@

clean:
	@make clean -C ${LIBFT_DIR}
	@echo "mini_shell cleaning..."
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${LIBFT}
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
