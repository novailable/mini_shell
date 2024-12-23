#ifndef MINI_SHELL_H
#define MINI_SHELL_H

#include "Libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>


//built_in

typedef struct s_envp {
	char	**envp;
	int		size;
}	t_envp;

char	**ft_split_2(char *str, char *delimiters, char *ignchars);

void	export(char **args, char ***envp);



#endif