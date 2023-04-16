/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setdata.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:48:26 by vde-prad          #+#    #+#             */
/*   Updated: 2023/04/16 13:05:22 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	It assigns the fd of the opened file to the output/input fd of the cmd
	executed.
	@param inputs Structure that contains the the parsed arguments.
	@param data Structure that contains the 1 the fd necessary for the execution.
*/
void	ft_setdata(t_pipe *data, t_inputs *inputs)
{
	if (inputs->args->ired_flag)
	{
		if (!access(inputs->args->infile, F_OK | R_OK))
			data->fdin = open(inputs->args->infile, O_RDONLY);
		else
		{
			ft_putstr_fd("No such file or directory\n", 2);
			exit(127);
		}
	}
	if (inputs->args->ored_flag || inputs->args->app_flag)
	{
		if (inputs->args->ored_flag)
			data->fdout = open(inputs->args->outfile,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (inputs->args->app_flag)
			data->fdout = open(inputs->args->outfile,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (data->fdout < 0)
		{
			ft_putstr_fd("Error: output file innaccesible\n", 2);
			exit(127);
		}
	}
}
