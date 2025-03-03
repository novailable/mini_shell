# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
<<<<<<< HEAD
#    By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 17:41:52 by aoo               #+#    #+#              #
#    Updated: 2025/03/03 15:57:29 by nsan             ###   ########.fr        #
=======
#    By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 17:41:52 by aoo               #+#    #+#              #
#    Updated: 2025/02/13 16:38:37 by aoo              ###   ########.fr        #
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -g #-Wall -Wextra -Werror
HEADER = -I Libft
RM = rm -rf

LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = main.c utils_str.c utils_ast.c utils_syntax_check.c \
		utils_token.c ast_args.c node_branch.c ast_redirection.c ast_branch.c ast_utils.c \
		utils.c redirection.c execution.c first_processing.c \
		built_in/export.c built_in/env.c built_in/unset.c built_in/pwd.c built_in/echo.c\
<<<<<<< HEAD
		built_in/cd.c built_in/history.c signals.c tokens.c free_all.c
=======
		built_in/cd.c built_in/history.c signals.c tokens.c
>>>>>>> 4cdeb0f6219f9fcf8d9941a671c90a0876c7291f

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
