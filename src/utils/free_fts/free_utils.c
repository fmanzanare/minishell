/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:13:56 by fmanzana          #+#    #+#             */
/*   Updated: 2023/05/07 17:13:57 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	free_vars(t_args *node)
{
	if (node->cmd_split)
		ft_free_arr(node->cmd_split);
	if (node->cmd_path)
		free(node->cmd_path);
	if (node->inf)
		ft_free_arr(node->inf);
	if (node->inf_flags)
		free(node->inf_flags);
	if (node->outf)
		ft_free_arr(node->outf);
	if (node->outf_flags)
		free(node->outf_flags);
	free(node);
}

void	free_list(t_args **args)
{
	t_args	*tmp;

	if (!args || !(*args))
		return ;
	while (*args)
	{
		tmp = (*args)->next;
		free_vars(*args);
		(*args) = tmp;
	}
	free(*args);
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
