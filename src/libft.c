#include "lem_in.h"

int	ft_atoi(char *str, int *num)
{
	// int			error;
	// char		c;
	int sign = 1;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}

	if (*str > '9' || *str < '0')
		return (0);
	*num = *str - '0';
	while (1)
	{
		str++;
		if (*str < '0' || *str > '9') {
			*num *= sign;
			return (1);
		}
		*num *= 10;
		*num += (*str - '0');
		if (*num > 10000000)
			return (0);
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_free(void *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
	return (0);
}

int	ft_error(char *str)
{
	int i = write(2, "Error\n", 7);
	i += write(2, str, ft_strlen(str));
	return (i - i);
}

char	*ft_strdup(char *str)
{
	int len = ft_strlen(str);
	char *dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	for (int i = 0; i < len; i++)
		dup[i] = str[i];
	dup[len] = '\0';
	return (dup);
}

void	*ft_malloc(size_t x)
{
	x += x;
	return (NULL);
}
