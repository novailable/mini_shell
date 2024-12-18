/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:11:04 by nsan              #+#    #+#             */
/*   Updated: 2024/12/16 17:17:33 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <ctype.h>
# include <fcntl.h> //open and flags
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h> //close, write

// size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
// int					ft_atoi(const char *str);
char				*ft_strdup(const char *src);
// char				*ft_strjoin(char const *s1, char c);
char				**ft_split(char const *s, char c);

#endif