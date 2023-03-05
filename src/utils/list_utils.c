#include "../../includes/minishell.h"

t_args	*create_node(char *cmd_line)
{
	t_args	*new;

	new = malloc(sizeof * new);
	new->cmd_line = cmd_line;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
