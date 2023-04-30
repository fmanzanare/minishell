#include "../../../includes/minishell.h"

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
