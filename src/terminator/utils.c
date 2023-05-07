#include "../../includes/minishell.h"

int	ft_check_alpha(char *arg, int i, const char *type, t_pipe *data)
{
	if (!ft_isalpha(arg[i]))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)type, 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid indetifier\n", 2);
		data->built_st = 1;
		return (1);
	}
	return (0);
}

/**
 * It creates a new node to fill the linked list
 * @param line value will set the node content
 * @param node
*/
t_env	*ft_new_node(char *line)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		exit(1);
	node->line = ft_strdup(line);
	return (node);
}
