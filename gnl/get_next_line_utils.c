#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "../includes/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char *str;
	unsigned char b;
	int i;
	int len;

	str = (char *)s;
	b = (unsigned char)c;
	i = -1;
	len = ft_strlen(str);
	while (++i < len + 1)
	{
		if (str[i] == b)
			return (str + i);
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *new;
	int i;
	int j;

	i = 0;
	j = 0;
	if (!(new = (char *)malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1) * sizeof(char))))
		return (0);
	while (*s1)
		new[i++] = *s1++;
	while (*s2)
		new[i++] = *s2++;
	new[i] = '\0';
	return (new);
}
