#include "../../includes/minishell.h"

void	cmd_arrayer(t_args *node)
{
	char	**tmp;

	if (node->ired_flag || node->delim)
	{
		tmp = command_spliter(node->cmd_line, '<');
		node->cmd_arr = command_spliter(tmp[0], ' ');
		ft_free_arr(tmp);
	}
	else if (node->ored_flag || node->app_flag)
	{
		tmp = command_spliter(node->cmd_line, '>');
		node->cmd_arr = command_spliter(tmp[0], ' ');
		ft_free_arr(tmp);
	}
}
