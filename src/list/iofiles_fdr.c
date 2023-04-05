#include "../../includes/minishell.h"

/**
 * Looks for the input file within the cmd_split variable.
 * @param *node Token/List Node to work with.
*/
static void	infile_fdr(t_args *node)
{
	int	i;

	i = 0;
	while (node->cmd_split[i])
	{
		if (node->cmd_split[i][0] == '<')
		{
			if (node->ired_flag)
				node->infile = node->cmd_split[i + 1];
			else if (node->hd_flag)
				node->delim = node->cmd_split[i + 1];
		}
		i++;
	}
}

/**
 * Looks for the output file within the cmd_split variable.
 * @param *node Token/List Node to work with.
*/
static void	outfile_fdr(t_args *node)
{
	int	i;

	i = 0;
	while (node->cmd_split[i])
	{
		if (node->cmd_split[i][0] == '>')
			node->outfile = node->cmd_split[i + 1];
		i++;
	}
}

/**
 * Checks the redirections flags and fills the io files.
 * @param *node Token/List Node to work with.
*/
void	iofiles_fdr(t_args *node)
{
	if (node->ired_flag || node->hd_flag)
	{
		infile_fdr(node);
		cmd_arrayer(node);
	}

	else if (node->ored_flag || node->app_flag)
	{
		outfile_fdr(node);
		cmd_arrayer(node);
	}
	else
		node->cmd_arr = node->cmd_split;
}
