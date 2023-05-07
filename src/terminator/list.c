#include "../../includes/minishell.h"

void	ft_add_var(char *var, t_pipe *data)
{
	t_env	*aux;
	t_env	*tmp;

	aux = data->env;
	while (aux->next)
		aux = aux->next;
	tmp = aux;
	tmp->next = ft_new_node(var);
	tmp->next->prev = tmp;
	tmp->next->next = NULL;
}

int	ft_find_var(char *var, t_pipe *data, t_env **target)
{
	t_env	*aux;
	int		len;

	len = ft_strlen(var);
	aux = data->env;
	while (aux)
	{
		if (!ft_strncmp(var, aux->line, len))
		{
			*target = aux;
			return (1);
		}
		aux = aux->next;
	}
	return (0);
}