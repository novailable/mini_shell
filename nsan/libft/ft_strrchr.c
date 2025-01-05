#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)(s);
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((str + i + 1)); //was modified here
		i--;
	}
	return (NULL);
}