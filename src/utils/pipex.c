/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:44:12 by vde-prad          #+#    #+#             */
/*   Updated: 2023/04/15 20:51:27 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_terminator(t_inputs *inputs, char **envp)
{
	int			i;
	int			childfd;
	t_pipedata	data;

	data.cpy_out = dup(STDOUT_FILENO);
	data.cpy_in = dup(STDIN_FILENO);
	data.fdin = dup(data.cpy_in);
	i = 0;
	while (i < inputs->lenght)
	{
		dup2(data.fdin, 0);
		close(data.fdin);
		if (i == inputs->lenght -1)
			data.fdout = data.cpy_out;
		else
		{
			if (pipe(data.pp) == 1)
			{
				perror("pipe failure");
				exit(127);
			}
			data.fdout = data.pp[1];
			data.fdin = data.pp[0];
		}
		dup2(data.fdout, 1);
		close(data.fdout);
		childfd = fork();
		if (childfd == 0)
		{
			execve(ft_getpath(envp, inputs->args->cmd_arr[0]),
				inputs->args->cmd_arr, envp);
			perror("execve failure");
			exit(127);
		}
		if (inputs->args->next)
			inputs->args = inputs->args->next;
		i++;
	}
	dup2(data.cpy_out, 1);
	dup2(data.cpy_in, 0);
	close(data.cpy_out);
	close(data.cpy_in);
	waitpid(childfd, &data.status, 0);
	run_to_head(&inputs->args);
	return (WEXITSTATUS(data.status));
}
// pp[0]--->lectura en pipe
// pp[1]--->escritura en pipe