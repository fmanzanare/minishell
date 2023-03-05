#include "../../includes/minishell.h"

void	run_to_head(t_args **args)
{
	while ((*args)->prev)
		*args = (*args)->prev;
}

void	run_to_tail(t_args **args)
{
	while ((*args)->next)
		*args = (*args)->next;
}

static t_args	*create_node(char *cmd_line)
{
	t_args	*new;

	new = malloc(sizeof * new);
	new->cmd_line = cmd_line;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	fill_command_lines(t_args **args, char **line_splited)
{
	int		i;

	i = 0;
	while (line_splited[i])
	{
		if (i == 0)
			*args = create_node(line_splited[i]);
		else
		{
			(*args)->next = create_node(line_splited[i]);
			(*args)->next->prev = *args;
			*args = (*args)->next;
		}
		i++;
	}
}
