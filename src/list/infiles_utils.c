/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:08:52 by fmanzana          #+#    #+#             */
/*   Updated: 2023/05/07 17:08:54 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Fills the infiles_flag array.
 * If '<' it places 1 in array.
 * If '<<' it places 2 in array.
 * @param *node Token/List Node to work with.
*/
void	infiles_flags_filler(t_args *node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	node->inf_flags = malloc(sizeof(int) * (node->inf_len));
	if (!node->inf_flags)
		exit(1);
	while (node->cmd_line[i])
	{
		if (node->cmd_line[i] == '<' && node->cmd_line[i + 1] != '<')
		{
			node->inf_flags[j] = 1;
			j++;
		}
		else if (node->cmd_line[i] == '<' && node->cmd_line[i + 1] == '<')
		{
			node->inf_flags[j] = 2;
			j++;
			i++;
		}
		i++;
	}
}

/**
 * Fills the infiles array with received infiles names.
 * @param *node Token/List Node to work with.
 * @param i Index where redirection is found.
 * @param *outf_idx Pointer to infiles array index.
*/
static void	infiles_filler(t_args *node, int i, int *inf_idx)
{
	int	len;
	int	idx;

	len = files_len(node, &i);
	node->inf[*inf_idx] = malloc(sizeof(char) * (len + 1));
	if (!node->inf)
		exit(1);
	idx = 0;
	while (node->cmd_line[i] != ' ' && !ft_isredir(node->cmd_line[i])
		&& node->cmd_line[i])
	{
		node->inf[*inf_idx][idx] = node->cmd_line[i];
		idx++;
		i++;
	}
	node->inf[*inf_idx][len] = '\0';
	(*inf_idx)++;
}

/**
 * Checks the infiles array length and calls infiles_filler function.
 * @param *node Token/List Node to work with.
*/
void	infiles_mngr(t_args *node, int *qmarks)
{
	int	i;
	int	inf_idx;

	i = 0;
	inf_idx = 0;
	node->inf_len = node->ired_flag + node->hd_flag;
	node->inf = malloc(sizeof(char *) * (node->inf_len + 1));
	if (!node->inf)
		exit(1);
	while (node->cmd_line[i])
	{
		qmarks[0] = check_s_qmark(node->cmd_line[i], qmarks[0]);
		qmarks[1] = check_d_qmark(node->cmd_line[i], qmarks[1]);
		if (node->cmd_line[i] == '<' && node->cmd_line[i + 1] != '<'
			&& !qmarks[0] && !qmarks[1])
			infiles_filler(node, i, &inf_idx);
		else if (node->cmd_line[i] == '<' && node->cmd_line[i + 1] == '<'
			&& !qmarks[0] && !qmarks[1])
		{
			i++;
			infiles_filler(node, i, &inf_idx);
		}
		i++;
	}
	node->inf[inf_idx] = NULL;
}
