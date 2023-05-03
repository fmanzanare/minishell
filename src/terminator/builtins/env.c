#include "../../../includes/minishell.h"

/**
 * It prints the linked list that stores the environment variables
 * 
 * @param data executor part structure
 * @param i iterator index
 * @param aux t_env linked list auxiliar pointer
 * @return -1
*/
int	ft_env(t_pipe *data)
{
	int		i;
	t_env	*aux;

	i = 0;
	aux = data->env;
	if (!aux)
		return (1);
	while (aux)
	{
		printf("%s\n", aux->line);
		aux = aux->next;
	}
	return (-1);
}
