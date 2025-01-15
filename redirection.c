#include "mini_shell.h"

void    re_input(char *file)
{
	int	fd_in;

	if (file && access(file, F_OK | R_OK | X_OK))
	{
		fd_in = open(file, O_RDONLY);
		if (fd_in < 0)
		{
			printf("%s", file);
			perror("error opening");
			return ;
		}
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

void    re_output(char *file, int append)
{
	int	fd_out;

	if (append)
		fd_out = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		printf("%s", file);
		perror("error opening");
		return ;
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

void	app_heredoc(char *eof)
{
	int		pipe_fd[2];
	char	*line;

	if (eof)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("error pie");
			exit(1);
		}
	}
	while (1)
	{
		line = readline ("> ");
		if (!line || strcmp(line, eof) == 0)
			break;
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
}

int main()
{
	int	org_fd;
	char buffer[20000];
	org_fd = dup(STDOUT_FILENO);
	char *file = readline("in : ");
	char *data = readline("> ");
	re_output(file, 1);
	printf("%s\n", data);
	free(file);
	dup2(org_fd, STDOUT_FILENO);
	file = readline("out : ");
	re_input(file);
	size_t n = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
	write(STDOUT_FILENO, buffer, n);

	
	// if (n > 0)
	// {
	// 	buffer[n] = '\0';
	// 	free(file);
	// 	file = readline("output : ");
	// 	re_output(file, 0);
	// 	write(STDOUT_FILENO, buffer, n);
	// }
}
