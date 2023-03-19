#include "../../includes/minishell.h"

/**
 * Checks if the node contains a redirection and if its output goes through pipe
 * If it contains a redirection, the "red_flag" is setted to 1 in the node.
 * If outputs goes through pipe, the "pipe_flag" is setted to 1 in the node.
 * Otherwise (for both cases) the flag is setted to 0.
 * @param *str Pipes and redirections strings.
 * @param *rp_idx Pointer to the index of the Pipes and redirections string.
 * @param *new The node to work with, which contains the flags.
*/
static void	red_pipe_checker(char *str, int *rp_idx, t_args *new)
{
	if (str[rp_idx[0]] == '<' || str[rp_idx[0]] == '>')
	{
		new->red_flag = 1;
		rp_idx[0]++;
	}
	if (str[rp_idx[0]] == '|')
	{
		new->pipe_flag = 1;
		rp_idx[0]++;
	}
}

/**
 * Creates a new node of the list.
 * @param cmd_line Command line to be added.
 * @param first_node Flag to indicate if it is the first argument.
 * @return New node.
*/
static t_args	*create_node(char *cmd, int node, int *rp_idx, t_inputs *inputs)
{
	t_args	*new;

	new = malloc(sizeof * new);
	new->cmd_line = ft_trim(cmd, node, inputs->lenght);
	new->cmd_arr = command_spliter(cmd, ' ');
	new->pipe_flag = 0;
	new->red_flag = 0;
	red_pipe_checker(inputs->pipes_redir, rp_idx, new);
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
	int		rp_idx;

	i = 0;
	rp_idx = 0;
	while (line_splited[i])
	{
		if (i == 0)
			*args = create_node(line_splited[i], i, &rp_idx, inputs);
		else
		{
			(*args)->next = create_node(line_splited[i], i, &rp_idx, inputs);
			(*args)->next->prev = *args;
			*args = (*args)->next;
		}
		i++;
	}
}
