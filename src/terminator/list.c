/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:11:37 by fmanzana          #+#    #+#             */
/*   Updated: 2023/05/07 17:12:42 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_count_list(t_pipe *data)
{
	t_env	*aux;
	int		len;

	len = 0;
	aux = data->env;
	while (aux)
	{
		len++;
		aux = aux->next;
	}
	return (len);
}

void	ft_mod_envp(t_pipe *data)
{
	t_env	*aux;
	int		len;
	int		i;

	i = 0;
	len = ft_count_list(data);
	data->envp = malloc((len + 1) * sizeof(char *));
	if (!data->envp)
		exit(127);
	aux = data->env;
	while (aux)
	{
		data->envp[i++] = ft_strdup(aux->line);
		aux = aux->next;
	}
	data->envp[i] = NULL;
}

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
