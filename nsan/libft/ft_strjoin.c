#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		i;
	int		j;
	int		total_len;

	i = 0;
	j = 0;
	if (!s1)
		return (NULL);
	total_len = (int)ft_strlen(s1) + (int)ft_strlen(s2) + 1;
	dest = malloc(sizeof(char) * total_len);
	if (!dest)
		return (NULL);
	while (i < (int)ft_strlen(s1))
	{
		dest[i] = s1[i];
		i++;
	}
	// dest[i] = c;
    // i++;
	while (i < total_len)
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}