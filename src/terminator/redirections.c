/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:48:26 by vde-prad          #+#    #+#             */
/*   Updated: 2023/05/07 17:02:01 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_sstrlen(char *s1, char *s2)
{
	int	l1;
	int	l2;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	if (l1 >= l2)
		return (l1);
	else
		return (l2);
}

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

static void	ft_here_doc(t_inputs *inputs, t_pipe *data)
{
	data->del1 = NULL;
	data->del2 = NULL;
	data->line = NULL;
	ft_get_delim(inputs, &data->del1, &data->del2);
	ft_iter_hd(inputs, data);
}

static int	ft_check_inf(t_inputs *inputs, t_pipe *data)
{
	int	i;
	int	fd;

	fd = 0;
	i = 0;
	while (inputs->args->inf[i])
	{
		if (inputs->args->inf_flags[i] == 1)
		{
			if (!access(inputs->args->inf[0], F_OK | R_OK))
			{
				if (inputs->args->ired_flag == i + 1 && data->ign_inf == 0)
					data->fdin = open(inputs->args->inf[i], O_RDONLY);
			}
			else
			{
				ft_putstr_fd("minishell : ", 2);
				ft_putstr_fd(inputs->args->inf[i], 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static void	ft_check_out(t_inputs *inputs, t_pipe *data)
{
	int	i;

	i = 0;
	while (i < inputs->args->outf_len)
	{
		if (inputs->args->outf_flags[i] == 1)
			data->fdout = open(inputs->args->outf[i],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (inputs->args->outf_flags[i] == 2)
			data->fdout = open(inputs->args->outf[i],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (i < inputs->args->outf_len - 1)
			close(data->fdout);
		if (data->fdout < 0)
		{
			ft_putstr_fd("Error: output file innaccesible\n", STDERR_FILENO);
			exit(127);
		}
		i++;
	}
}

/**
	It assigns the fd of the opened file to the output/input fd of the cmd
	executed.
	@param inputs Structure that contains the the parsed arguments.
	@param data Structure that contains the 1 the fd necessary for the execution.
*/
int	ft_setdata(t_inputs *inputs, t_pipe *data)
{
	if (inputs->args->ored_flag || inputs->args->app_flag)
		ft_check_out(inputs, data);
	if (inputs->args->inf_len)
	{
		if (inputs->args->inf_flags[inputs->args->inf_len - 1] == 1)
			data->ign_inf = 0;
		else if (inputs->args->inf_flags[inputs->args->inf_len - 1] == 2)
			data->ign_inf = 1;
		if (inputs->args->hd_flag > 0)
			ft_here_doc(inputs, data);
		return (ft_check_inf(inputs, data));
	}
	return (0);
}
