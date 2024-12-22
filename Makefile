# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 17:41:52 by aoo               #+#    #+#              #
#    Updated: 2024/12/21 21:23:26 by aoo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mini_shell
CC = cc
CFLAGS = -g #-Wall -Wextra -Werror
HEADER = -I Libft
RM = rm -rf

LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = mini_shell.c ft_split_2.c

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT}
	@echo "${NAME} compiling..."
	@${CC} ${CFLAGS} ${HEADER} -lft -L${LIBFT_DIR} ${OBJS} ${LIBFT} -lreadline -o ${NAME}
	@echo "${NAME} created."
# cc -g -Wall -Wextra -Werror -I ft_printf -I Libft -I minilibix-linux -lft -L./Libft -L./ft_printf -L./minilibx-linux get_next_line.o get_next_line_utils.o fdf.o read_map.o draw_map.o bresenham.o ./ft_printf/libftprintf.a ./Libft/libft.a ./minilibx-linux/libmlx.a -lXext -lX11 -lm -lz -o fdf
#gcc -o test test1.c -L./minilibx-linux -I minilibix-linux ./minilibx-linux/libmlx.a -lXext -lX11 -lm -lz
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
