#include "../../includes/minishell.h"

int	array_len(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}
