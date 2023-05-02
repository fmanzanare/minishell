#include "../../includes/minishell.h"

/**
 * Calculates the length of the file name.
 * @param *node Token/List Node to work with.
 * @param *i Pointer to the cmd_line index.
*/
int	files_len(t_args *node, int *i)
{
	int	len;
	int	j;

	len = 0;
	(*i)++;
	while (node->cmd_line[(*i)] == ' ')
		(*i)++;
	j = (*i);
	while (node->cmd_line[j] != ' ' && !ft_isredir(node->cmd_line[j++]))
		len++;
	return (len);
}
