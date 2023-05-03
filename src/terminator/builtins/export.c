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
	t_env	*tmp;

	aux = data->env;
	while (aux->next)
		aux = aux->next;
	tmp = aux;
	tmp->next = ft_new_node(var);
	tmp->next->prev = tmp;
	tmp->next->next = NULL;
}

int	ft_check_alpha(char *arg, int i, const char *type)
{
	if (!ft_isalpha(arg[i]))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)type, 2);
		ft_putstr_fd(": `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid indetifier\n", 2);
		return (1);
	}
	return (0);
}

/**
 * It checks that the variable name is valid, checks if the variable
 * already exist and create it or modify the value.
 * 
 * @param arg the complete line of one of the arguments passed to export
 * @param data structure of the executor part
 * @param i iterator index
 * @param var the only variable name that will be export
 * @param aux t_env auxiliar pointer
*/
static void	ft_set_variable(char *arg, t_pipe *data)
{
	int		i;
	char	*var;
	t_env	*aux;

	i = 0;
	var = NULL;
	if (ft_check_alpha(arg, i, "export"))
		return ;
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
}

/**
 * It creates a new variable or modify the value of an existing variable
 * 
 * @param inputs parser part structure 
 * @param data executor part structure
 * @param i iterator index
 * @return -1
*/
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
		ft_set_variable(inputs->args->cmd_arr[i++], data);
	return (-1);
}
