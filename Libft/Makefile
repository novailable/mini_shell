# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 12:01:02 by aoo               #+#    #+#              #
#    Updated: 2025/01/27 21:24:05 by aoo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf

SRCS = ft_isalpha.c ft_isdigit.c ft_isdigit.c  ft_isalnum.c  ft_isascii.c ft_strstr.c ft_strndup.c\
       ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c  ft_strlcpy.c \
       ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strcmp.c ft_memchr.c \
       ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
       ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
       ft_putendl_fd.c ft_putnbr_fd.c ft_atoi_vali.c ft_atoi_base.c ft_lowercase.c ft_uppercase.c \
	   ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
	   ft_lstdelnode.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_strtokr_c.c free_strs.c
OBJS = ${SRCS:.c=.o}


all : compile_msg ${NAME}
	@echo "${NAME} library created."

compile_msg :
	@echo "libft compiling..."

${NAME} : ${OBJS}
	@${AR} $@ $^

%.o : %.c
	@${CC} ${CFLAGS} -c $< -o $@

clean :
	@echo "libft cleaning..."
	@${RM} ${OBJS} ${B_OBJS}

fclean : clean
	@echo "${NAME} cleaning..."
	@${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re
