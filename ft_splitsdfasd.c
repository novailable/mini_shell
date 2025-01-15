#include "mini_shell.h"

int	check_char(char c, char *charset)
{
	int	i;

	i = 1;
	while (charset[i - 1])
	{
		if (charset[i - 1] == c)
			return (i);
		i++;
	}
	return (0);
}

static int	count_word(char *s, char *delimiters, char *ignchar)
{
	int	count;
	int	in_word;
	int	ign_word;

	count = 0;
	in_word = 0;
	ign_word = 0;
	while (*s)
	{
		if (check_char(*s, ignchar))
			ign_word = !ign_word;
		if (!ign_word && !check_char(*s, delimiters) && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (check_char(*s, delimiters))
			in_word = 0;
		s++;
	}
	return (count);
}

// #include <stdio.h>

// char	**ft_split(char *str, char *delimiter, char	*ignchar)
// {
// 	printf("count : %d\n", count_word(str, delimiter, ignchar));
// 	return (NULL);
// }