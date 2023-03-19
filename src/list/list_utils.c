#include "../../includes/minishell.h"

/**
 * Removes the first and last space of the cmd_line
 * @param *str String to be trimmed.
 * @param first_node Flag to indicate if it is the first cmd_line.
 * @return Trimmed string.
*/
char	*ft_trim(char *str, int node, int input_len)
{
	int		len;
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 1;
	if (!node)
		j = 0;
	len = ft_strlen(str) - 1;
	if (node < (input_len - 1) && node)
		len--;
	res = malloc(sizeof(char *) * len);
	while (i < len)
	{
		res[i] = str[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}
