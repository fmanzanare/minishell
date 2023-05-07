/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:09:59 by fmanzana          #+#    #+#             */
/*   Updated: 2023/05/07 17:10:02 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * It prints the linked list that stores the environment variables
 *
 * @param data executor part structure
 * @param i iterator index
 * @param aux t_env linked list auxiliar pointer
 * @return -1
*/
int	ft_env(t_inputs *inputs, t_pipe *data)
{
	int		i;
	t_env	*aux;

	i = 0;
	aux = data->env;
	if (inputs->args->cmd_arr[1])
	{
		ft_putstr_fd("env : ", 2);
		ft_putstr_fd(inputs->args->cmd_arr[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		data->built_st = 127;
		return (-1);
	}
	if (!aux)
		return (1);
	while (aux)
	{
		printf("%s\n", aux->line);
		aux = aux->next;
	}
	return (-1);
}
