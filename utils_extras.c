/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsan <nsan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 05:36:22 by nsan              #+#    #+#             */
/*   Updated: 2025/01/14 06:08:35 by nsan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int history_write(char *input)
{
	int open_fd;
	int write_fd;

	add_history(input);
	open_fd = open(".mini_history", O_RDWR|O_CREAT|O_APPEND, 0666);
	write_fd = write(open_fd, input, ft_strlen(input));
	write(open_fd, "\n", 1);
	if(open_fd == -1 || write_fd == -1)
	{
		printf("open or write error\n");
		close(open_fd);
		return (0);
	}
	close(open_fd);
	return (1);
}

void history_output(char *input)
{
	char buf[1024];
	int sz;
	int another_fd;

	if(input)
	{
		if (history_write(input))
		{
			if (!ft_strncmp(input, "history", 7))
			{
				another_fd = open(".mini_history", O_RDONLY);
				sz = read(another_fd, buf, sizeof(buf)-1);
				if(sz > 0)
				{
					handle_newline(buf, sz);
					buf[sz] = '\0';
				}
				if (sz < 0) {
					perror("Error reading file");
				}
			}
		}
	}
}
