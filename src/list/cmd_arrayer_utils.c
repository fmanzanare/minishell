#include "../../includes/minishell.h"

char	*cmdjoin(char *str)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc(sizeof(char) * ft_strlen(str));
	if (!dst)
		exit(1);
	while (str[i] && !ft_isredir(str[i]))
	{
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	array_len(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}
