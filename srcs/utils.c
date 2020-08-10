#include "../includes/cub3d.h"

int	ft_atoi(const char *str)
{
	int i;
	int sign;
	int res;

	i = 0;
	sign = 0;
	res = 0;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r' ||
			str[i] == '\v' || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sign++;
		i++;
	}
	else if (str[i] == '+')
		i++;

	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (sign % 2 == 1)
		res = -res;
	return (res);
}

int	ft_isdigit(int c)
{
	unsigned char a;

	a = (unsigned char)c;
	if (a >= '0' && a <= '9')
		return (1);
	return(0);
}


char	*ft_substr(char const *src, unsigned int start, size_t len)
{
	char *new;
	int srclen;
	int i;

	srclen = ft_strlen((char *)src);
	i = 0;
	if (srclen - start >= len)
	{
		if (!(new = (char *)malloc((len + 1) * sizeof(char))))
			return (0);
		while (len)
		{
			new[i++] = src[start++];
			len--;
		}
		new[i] = '\0';
	}
	if (srclen - start < len)
	{
		if (!(new = (char *)malloc((srclen - start + 1) * sizeof(char))))
			return (0);
		while (src[start])
			new[i++] = src[start++];
		new[i] = '\0';
	}
	return (new);
}

void	*ft_bzero(void *b, size_t len)
{
	unsigned char *a;
	int i;

	i = 0;
	a = b;
	while (len > 0)
	{
		a[i] = 0;
		i++;
		len--;
	}
	return (b);
}
