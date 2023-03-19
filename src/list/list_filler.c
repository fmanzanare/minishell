#include "../../includes/minishell.h"

static void red_pipe_checker(char *str, t_args *new)
{
	if (*str == '<' || *str == '>')
	{
		new->red_flag = 1;
		str++;
	}
	if (*str == '|')
	{
		new->pipe_flag = 1;
		str++;
	}
}

/**
 * Creates a new node of the list.
 * @param cmd_line Command line to be added.
 * @param first_node Flag to indicate if it is the first argument.
 * @return New node.
*/
static t_args	*create_node(char *cmd_line, int node, int len, t_inputs *inputs)
{
	t_args	*new;

	new = malloc(sizeof * new);
	new->cmd_line = ft_trim(cmd_line, node, len);
	new->cmd_arr = command_spliter(cmd_line, ' ');
	red_pipe_checker(inputs->pipes_redir, new);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/**
 * Receives the arguments and the full line splited by "|" and fills the list
 * @param **args Pointer to the "args" struct
 * @param **line_splited Received line splited by "|".
*/
void	fill_command_lines(t_args **args, char **line_splited, t_inputs *inputs)
{
	int		i;
	int		input_len;

	i = 0;
	input_len = input_size(line_splited);
	while (line_splited[i])
	{
		if (i == 0)
			*args = create_node(line_splited[i], i, input_len, inputs);
		else
		{
			(*args)->next = create_node(line_splited[i], i, input_len, inputs);
			(*args)->next->prev = *args;
			*args = (*args)->next;
		}
		i++;
	}
}
