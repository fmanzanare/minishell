#include "../../includes/minishell.h"

/**
 * It resizes the actual cmd_arr to receive new parameters.
 * @param *node Toke/List Node to work with.
 * @param idx Command index.
*/
static void	resize_arr(t_args *node, int idx)
{
	char	**tmp;
	char	arr_len;
	int		i;

	i = 0;
	tmp = node->cmd_arr;
	arr_len = array_len(node->cmd_arr);
	node->cmd_arr = malloc(sizeof(char *) * (arr_len + 2));
	while (tmp[i])
	{
		node->cmd_arr[i] = cmdjoin(tmp[i]);
		i++;
	}
	node->cmd_arr[i] = cmdjoin(node->cmd_split[idx]);
	i++;
	node->cmd_arr[i] = NULL;
	ft_free_arr(tmp);
}

/**
 * Joins the command into cmd_arr variable.
 * @param *node Token/List Node to work with.
 * @param idx Command index.
*/
static void	add_to_cmd_array(t_args *node, int idx)
{
	int		len;

	len = 0;
	if (!node->cmd_arr)
	{
		node->cmd_arr = malloc(sizeof(char *) + 1);
		if (!node->cmd_arr)
			exit(1);
		node->cmd_arr[0] = cmdjoin(node->cmd_split[idx]);
		node->cmd_arr[1] = NULL;
	}
	else
		resize_arr(node, idx);
}

/**
 * It fills the cmd_arr variable.
 * @param *node Token/List Node to work with.
 * @param i Index.
 * @param j Index.
*/
void	cmd_arrayer(t_args *node, int i, int j)
{
	int	red_flag;
	int	cmd_idx;

	red_flag = 0;
	cmd_idx = -1;
	while (node->cmd_split[i])
	{
		if (!red_flag && !ft_isredir(node->cmd_split[i][0]))
			cmd_idx = i;
		if (cmd_idx >= 0)
		{
			add_to_cmd_array(node, cmd_idx);
			cmd_idx = -1;
		}
		j = 0;
		while (node->cmd_split[i][j])
		{
			if (ft_isredir(node->cmd_split[i][j]) && !red_flag)
				red_flag = 1;
			else if (!ft_isredir(node->cmd_split[i][j]))
				red_flag = 0;
			j++;
		}
		i++;
	}
}
