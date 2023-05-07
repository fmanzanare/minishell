/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iofiles_fdr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:09:00 by fmanzana          #+#    #+#             */
/*   Updated: 2023/05/07 17:09:01 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Fills the outfiles_flag array.
 * If '>' it places 1 in array.
 * If '>>' it places 2 in array.
 * @param *node Token/List Node to work with.
*/
static void	outfiles_flag_filler(t_args *node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	node->outf_flags = malloc(sizeof(int) * (node->outf_len));
	if (!node->outf_flags)
		exit(1);
	while (node->cmd_line[i])
	{
		if (node->cmd_line[i] == '>' && node->cmd_line[i + 1] != '>')
		{
			node->outf_flags[j] = 1;
			j++;
		}
		else if (node->cmd_line[i] == '>' && node->cmd_line[i + 1] == '>')
		{
			node->outf_flags[j] = 2;
			j++;
			i++;
		}
		i++;
	}
}

/**
 * Fills the outfiles array with received outfiles names.
 * @param *node Token/List Node to work with.
 * @param i Index where redirection is found.
 * @param *outf_idx Pointer to outfiles array index.
*/
static void	outfiles_filler(t_args *node, int i, int *outf_idx)
{
	int	len;
	int	idx;

	len = files_len(node, &i);
	node->outf[*outf_idx] = malloc(sizeof(char) * (len + 1));
	if (!node->outf)
		exit(1);
	idx = 0;
	while (node->cmd_line[i] != ' ' && !ft_isredir(node->cmd_line[i])
		&& node->cmd_line[i])
	{
		node->outf[*outf_idx][idx] = node->cmd_line[i];
		idx++;
		i++;
	}
	node->outf[*outf_idx][len] = '\0';
	(*outf_idx)++;
}

/**
 * Checks the outfiles array length and calls outfiles_filler function.
 * @param *node Token/List Node to work with.
*/
static void	outfiles_mngr(t_args *node, int *qmarks)
{
	int	i;
	int	outf_idx;

	i = 0;
	outf_idx = 0;
	node->outf_len = node->ored_flag + node->app_flag;
	node->outf = malloc(sizeof(char *) * (node->outf_len + 1));
	if (!node->outf)
		exit(1);
	while (node->cmd_line[i])
	{
		qmarks[0] = check_s_qmark(node->cmd_line[i], qmarks[0]);
		qmarks[1] = check_d_qmark(node->cmd_line[i], qmarks[1]);
		if (node->cmd_line[i] == '>' && node->cmd_line[i + 1] != '>'
			&& !qmarks[0] && !qmarks[1])
			outfiles_filler(node, i, &outf_idx);
		else if (node->cmd_line[i] == '>' && node->cmd_line[i + 1] == '>'
			&& !qmarks[0] && !qmarks[1])
		{
			i++;
			outfiles_filler(node, i, &outf_idx);
		}
		i++;
	}
	node->outf[outf_idx] = NULL;
}

/**
 * Checks the redirections flags and fills the io files.
 * @param *node Token/List Node to work with.
*/
void	iofiles_fdr(t_args *node)
{
	int	qmarks[2];

	qmarks[0] = 0;
	qmarks[1] = 0;
	if (node->hd_flag || node->ired_flag)
	{
		infiles_mngr(node, qmarks);
		infiles_flags_filler(node);
	}
	if (node->ored_flag || node->app_flag)
	{
		outfiles_mngr(node, qmarks);
		outfiles_flag_filler(node);
	}
	if (!node->hd_flag && !node->app_flag
		&& !node->ired_flag && !node->ored_flag)
		node->cmd_arr = node->cmd_split;
	else
		cmd_arrayer(node, 0, 0);
}
