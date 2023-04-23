#include "libft.h"

int	ft_isredir(char c)
{
	if (c == '>')
		return (1);
	else if (c == '<')
		return (2);
	else
		return (0);
}
