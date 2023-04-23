#include "../../includes/minishell.h"

void	cmd_arrayer(t_args *node)
{
	char	**tmp;

	if ((node->ired_flag))
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

static void	redir_first(t_args *node)
{
	char	**tmp;
	int		len;

	len = 0;
	if ((node->ired_flag || node->hd_flag)
		&& !(node->app_flag || node->ored_flag))
	{
		tmp = command_spliter(node->cmd_line, '<');
		len = array_len(tmp);
		node->cmd_arr = command_spliter(tmp[len - 1], ' ');
	}
	else if (!(node->ired_flag || node->hd_flag)
		&& (node->app_flag || node->ored_flag))
	{
		tmp = command_spliter(node->cmd_line, '>');
		len = array_len(tmp);
		node->cmd_arr = command_spliter(tmp[len - 1], ' ');
	}
}

static void	cmd_arrayer_v2(t_args *node)
{
	if (ft_isredir(node->cmd_split[0][0]))
		redir_first(node);
	else
		cmd_first();
}
