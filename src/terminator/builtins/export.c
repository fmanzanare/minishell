#include "../../../includes/minishell.h"

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

static void	ft_add_var(char *var, t_pipe *data)
{
	t_env	*aux;
	t_env	*prev;

	aux = data->env;
	while (aux)
	{
		if (aux->next == NULL)
			prev = aux;
		aux = aux->next;
		if (aux == NULL)
		{
			aux = ft_new_node(var);
			aux->next = NULL;
			prev->next = aux;
			return ;
		}
	}
}

static int	ft_check_alpha(char *arg, int i)
{
	if (!ft_isalpha(arg[i]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid indetifier\n", 2);
		return (1);
	}
	return (0);
}

static int	ft_set_variable(char *arg, t_pipe *data)
{
	int		i;
	char	*var;
	t_env	*aux;

	i = 0;
	var = NULL;
	if (ft_check_alpha(arg, i))
		return (0);
	while (arg[i])
	{
		if (arg[i] == '=')
		{
			var = ft_substr(arg, 0, i + 1);
			if (ft_find_var(var, data, &aux))
			{
				free(aux->line);
				aux->line = ft_strdup(arg);
			}
			else
				ft_add_var(arg, data);
		}
		i++;
	}
	return (1);
}

int	ft_export(t_inputs *inputs, t_pipe *data)
{
	int	i;

	i = 1;
	if (!inputs->args->cmd_arr[i])
	{
		ft_env(data);
		return (-1);
	}
	while (inputs->args->cmd_arr[i])
	{
		ft_set_variable(inputs->args->cmd_arr[i], data);
		i++;
	}
	return (-1);
}
