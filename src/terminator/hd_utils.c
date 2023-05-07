/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:17:16 by fmanzana          #+#    #+#             */
/*   Updated: 2023/05/07 17:17:30 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	ft_get_delim(t_inputs *inputs, char **del1, char **del2)
{
	int	i;

	i = 0;
	while (i < inputs->args->inf_len)
	{
		if (inputs->args->hd_flag == 1 && inputs->args->inf_flags[i] == 2)
			*del1 = inputs->args->inf[i];
		else if (inputs->args->hd_flag > 1)
		{
			i = inputs->args->inf_len - 1;
			while (i > 0)
			{
				if (inputs->args->inf_flags[i] == 2 && !(*del2))
					*del2 = inputs->args->inf[i];
				else if (inputs->args->inf_flags[i] == 2)
				{
					*del1 = inputs->args->inf[i];
					return ;
				}
				i--;
			}
		}
		i++;
	}
}

static void	ft_iter_fullhd(t_inputs *inputs, t_pipe *data, int flag)
{
	while (1)
	{
		data->line = readline("> ");
		if (!data->line)
			break ;
		if (!ft_strncmp(data->line, data->del1, 1000)
			&& inputs->args->hd_flag == 1)
			break ;
		else if (!ft_strncmp(data->line, data->del1, 1000))
		{
			flag = 1;
			free(data->line);
			continue ;
		}
		if (data->del2 && !ft_strncmp(data->line, data->del2, 1000) && flag)
			break ;
		if (flag)
		{
			ft_putstr_fd(data->line, data->ppp[1]);
			ft_putstr_fd("\n", data->ppp[1]);
		}
		free(data->line);
	}
}

static void	ft_iter_hd(t_inputs *inputs, t_pipe *data)
{
	int		flag;

	flag = 1;
	if (inputs->args->hd_flag > 1)
		flag = 0;
	if (pipe(data->ppp) == 1)
		exit(127);
	ft_iter_fullhd(inputs, data, flag);
	if (data->ign_inf == 1)
		data->fdin = data->ppp[0];
	close(data->ppp[1]);
}

void	ft_here_doc(t_inputs *inputs, t_pipe *data)
{
	data->del1 = NULL;
	data->del2 = NULL;
	data->line = NULL;
	ft_get_delim(inputs, &data->del1, &data->del2);
	ft_iter_hd(inputs, data);
}
