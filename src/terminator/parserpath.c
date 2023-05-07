/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:45:50 by vde-prad          #+#    #+#             */
/*   Updated: 2023/05/07 15:48:53 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
	free memory of 'paths' variable
	@param paths contains the possible paths for the cmd
	@param n iterator index
*/
static void	ft_freepaths(char **paths)
{
	int	n;

	n = 0;
	while (paths[n])
	{
		free(paths[n]);
		n++;
	}
	free(paths);
}

/**
	Put a '/' and the cmd at the end of the possible paths 
	@param paths the possible paths
	@param cmd the cmd being searched for
	@param sufix the '/' and the cmd together
	@param i iterator index
*/
static void	ft_setssufix(char	**paths, char	*cmd)
{
	char	*sufix;
	int		i;

	i = 0;
	sufix = malloc((ft_strlen(cmd) + 1) * sizeof(char));
	if (!sufix)
		ft_putstr_fd("Allocation memory fail\n", 2);
	sufix = ft_strjoin("/", cmd);
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], sufix);
		i++;
	}
	free(sufix);
}

/**
	It gets the correct path to the cmd passed by arg
	@param i Index iterator
	@param res The correct path with the cmd included
	@param paths The possible paths for the cmd
	@param cmd The cmd whose path is been looking for
	@return the string which contains the path of the cmd
*/
static char	*ft_chkaccess(char	**paths, char	*cmd)
{
	int		i;
	char	*res;

	ft_setssufix(paths, cmd);
	res = malloc(3 * sizeof(char *));
	if (!res)
		return (0);
	i = 0;
	while (paths[i])
	{
		if (!access(paths[i], F_OK | R_OK))
		{
			res = ft_strdup(paths[i]);
			ft_freepaths(paths);
			return (res);
		}
		i++;
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	free(res);
	ft_freepaths(paths);
	res = NULL;
	exit(127);
}

/**
	It gets the path of the cmd, included the cmd
	@param ep Environment variables
	@param cmd Cmd whose path is looking for
	@param i Index iterator
	@param pathline The possible path for cmd
	@param paths The possible paths splited
	@return The path of the cmd, cmd included
*/
char	*ft_getpath(t_pipe *data, char *cmd)
{
	unsigned int	i;
	char			*pathline;
	char			**paths;

	paths = NULL;
	i = 0;
	while (data->envp[i])
	{
		pathline = ft_strnstr(data->envp[i], "PATH", 5);
		if (pathline)
		{
			pathline = ft_substr(pathline, 5, 200);
			paths = ft_split(pathline, ':');
			break ;
		}
		i++;
	}
	free(pathline);
	return (ft_chkaccess(paths, cmd));
}
