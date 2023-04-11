/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:44:12 by vde-prad          #+#    #+#             */
/*   Updated: 2023/04/11 16:27:58 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child(t_argdata data, char **ep)
{
	char	*path;

	path = ft_getpath(ep, data.cmd[0]);
	dup2(data.fdin, STDIN_FILENO);
	dup2(data.pp[1], STDOUT_FILENO);
	close(data.pp[1]);
	close(data.pp[0]);
	execve(path, data.options[0], ep);
	ft_putstr_fd("Error: execve failed\n", 2);
	exit(-1);
}

static void	ft_freeclose(t_argdata *data)
{
	close(data->fdin);
	close(data->fdout);
	free(data->cmd[1]);
	free(data->options[1]);
	free(data->cmd[0]);
	free(data->options[0]);
}

int	terminator(int ac, char **av, char **ep)
{
	int			pid;
	int			pid1;
	int			status;
	t_argdata	data;

	if (ac == 5)
		ft_setdata(&data, av, ac);
	else
	{
		ft_putstr_fd("Error: number of arguments incorrect\n", 2);
		exit(127);
	}
	pid = fork();
	if (pid == 0)
	{
		pid1 = fork();
		if (pid1 == 0)
			child(data, ep);
		child2(data, ep);
	}
	close(data.pp[1]);
	close(data.pp[0]);
	waitpid(pid, &status, 0);
	ft_freeclose(&data);
	return (WEXITSTATUS(status));
}
// pp[0]--->lectura en pipe
// pp[1]--->escritura en pipe
// char	*argv[] = {"/bin/cat", "-e", 0, "/usr/bin/wc", "-l", 0};

// int main(int argc, char *argv[], char **ep)
// {
//     char	**paths;
//     int		i;
// 
//     i = -1;
//     (void)argc;
//     (void)argv;
//     paths = ft_getpath(ep, "cat", "-e");
//     while (paths[++i])
//     {
//         puts(paths[i]);
//         free(paths[i]);
//     }
// }
