/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:10:27 by fmanzana          #+#    #+#             */
/*   Updated: 2023/05/07 17:10:28 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * It deletes and free the node that contains the var that is unset
 *
 * @param aux t_env auxiliar pointer
 * @param data structure from the executor part
*/
static void	ft_rm_var(t_env *aux, t_pipe *data)
{
	if (aux->next == NULL && aux->prev)
		aux->prev->next = NULL;
	else if (aux->prev)
		aux->prev->next = aux->next;
	if (aux->prev == NULL && aux->next)
	{
		aux->next->prev = NULL;
		data->env = aux->next;
	}
	else if (aux->next)
		aux->next->prev = aux->prev;
	free(aux->line);
	free(aux);
}

/**
 * It checks that the argument is valid, it substract the variable name
 * from the argument, find it in the linked list and call the function that
 * removes it from the liked list.
 *
 * @param arg the complete argument passed to ft_unset function
 * @param data structure of executor part
 * @param i iterator index
 * @param var the name of the var that will be unset
 * @param aux t_env auxiliar pointer to iterate the linked list
*/
static void	ft_unset_var(char *arg, t_pipe *data)
{
	int		i;
	char	*var;
	t_env	*aux;

	i = 0;
	var = NULL;
	if (ft_check_alpha(arg, i, "unset", data))
		return ;
	while (arg[i])
	{
		if (arg[i + 1] == '\0')
		{
			var = ft_substr(arg, 0, i + 1);
			if (ft_find_var(var, data, &aux))
				ft_rm_var(aux, data);
			free(var);
		}
		i++;
	}
	ft_mod_envp(data);
}

/**
 * Unset the passed variable from thee environment variables
 * @param inputs structure of the parser part
 * @param data structure of executor part
 * @param aux auxiliar pointer to iterate the linked list t_env
 * @param i iterator index
 * @return return -1
*/
int	ft_unset(t_inputs *inputs, t_pipe *data)
{
	t_env	*aux;
	int		i;

	i = 1;
	aux = data->env;
	if (!inputs->args->cmd_arr[i])
		return (-1);
	while (inputs->args->cmd_arr[i])
		ft_unset_var(inputs->args->cmd_arr[i++], data);
	return (-1);
}
