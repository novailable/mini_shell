/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoo <aoo@student.42singapore.sg>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 05:36:22 by nsan              #+#    #+#             */
/*   Updated: 2025/02/13 16:41:00 by aoo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	history_write(char *input)
{
	int	open_fd;

	add_history(input);
	open_fd = open(".mini_history", O_RDWR | O_CREAT | O_APPEND, 0666);
	write(open_fd, input, ft_strlen(input));
	write(open_fd, "\n", 1);
	if (open_fd == -1)
		return (write(2, "open or write error\n", 21), 1);
	close(open_fd);
	return (0);
}

void	print_history(char *buffer)
{
	char	**h_lines;
	int		count;
	int		i;

	h_lines = ft_split(buffer, "\n");
	count = 0;
	while (h_lines[count])
		count++;
	if (count > 500)
		count -= 500;
	else
		count = 0;
	i = 1;
	while (h_lines[count])
		printf("%5d  %s\n", i++, h_lines[count++]);
	free_strs(h_lines);
}

int	history_output(void)
{
	char	buffer[700000];
	size_t	size;
	int		history_fd;

	history_fd = open(".mini_history", O_RDONLY);
	if (history_fd < 0)
		return (perror("minishell: error opening hisotry"), 1);
	size = read(history_fd, buffer, sizeof(buffer) - 1);
	buffer[size] = '\0';
	print_history(buffer);
	close(history_fd);
	return (0);
}
