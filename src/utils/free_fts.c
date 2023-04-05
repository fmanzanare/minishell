#include "../../includes/minishell.h"

void	free_list(t_args **args)
{
	t_args	*tmp;

	run_to_head(*(&args));
	if (!args || !(*args))
		return ;
	while (*args)
	{
		tmp = (*args)->next;
		//ft_free_arr((*args)->split);
		free(*args);
		(*args) = tmp;
	}
	(*args) = NULL;
}

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
