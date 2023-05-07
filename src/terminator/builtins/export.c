/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:10:16 by fmanzana          #+#    #+#             */
/*   Updated: 2023/05/07 17:10:17 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
void	ft_set_variable(char *arg, t_pipe *data)
{
	int		i;
	char	*var;
	t_env	*aux;

	i = 0;
	var = NULL;
	if (ft_check_alpha(arg, i, "export", data))
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
	ft_mod_envp(data);
}

/**
 * It creates a new variable or modify the value of an existing variable
 *
 * @param inputs parser part structure
 * @param data executor part structure
 * @param i iterator index
 * @return -1
*/
int	ft_export(char **cmd_arr, t_pipe *data, t_inputs *inputs)
{
	int	i;

	i = 1;
	if (!cmd_arr[i])
	{
		ft_env(inputs, data);
		return (-1);
	}
	while (cmd_arr[i])
		ft_set_variable(cmd_arr[i++], data);
	return (-1);
}
