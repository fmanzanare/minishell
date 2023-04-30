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
	if (str[*rp_idx] == '<' && str[*rp_idx + 1] != '<')
	{
		new->ired_flag += 1;
		(*rp_idx) += 2;
	}
	else if (str[*rp_idx] == '>' && str[*rp_idx + 1] != '>')
	{
		new->ored_flag += 1;
		(*rp_idx) += 2;
	}
	else if (str[*rp_idx] == '>' && str[*rp_idx + 1] == '>')
	{
		new->app_flag += 1;
		(*rp_idx) += 3;
	}
	else if (str[*rp_idx] == '<' && str[*rp_idx + 1] == '<')
	{
		new->hd_flag += 1;
		(*rp_idx) += 3;
	}
}

static void	zeros_and_nulls_init(t_args *node)
{
	node->cmd_line = NULL;
	node->cmd_split = NULL;
	node->cmd_arr = NULL;
	node->cmd_path = NULL;
	node->inf = NULL;
	node->inf_flags = NULL;
	node->inf_len = 0;
	node->outf = NULL;
	node->outf_flags = NULL;
	node->outf_len = 0;
	node->pipe_flag = 0;
	node->ored_flag = 0;
	node->ired_flag = 0;
	node->app_flag = 0;
	node->hd_flag = 0;
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
	node = 0;
	zeros_and_nulls_init(new);
	new->cmd_line = cmd;
	new->cmd_split = pipe_spliter(cmd, ' ');
	while (inputs->pipes_redir[*rp_idx] != '|'
		&& inputs->pipes_redir[*rp_idx] != '\0')
		red_pipe_checker(inputs->pipes_redir, rp_idx, new);
	if (inputs->pipes_redir[*rp_idx] == '|')
	{
		new->pipe_flag = 1;
		(*rp_idx) += 2;
	}
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
		{
			*args = create_node(line_splited[i], i, &rp_idx, inputs);
			iofiles_fdr(*args);
		}
		else
		{
			(*args)->next = create_node(line_splited[i], i, &rp_idx, inputs);
			iofiles_fdr((*args)->next);
			(*args)->next->prev = *args;
			*args = (*args)->next;
		}
		i++;
	}
}
