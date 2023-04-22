#include "libft.h"

int	ft_isredir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	else
		return (0);
}
