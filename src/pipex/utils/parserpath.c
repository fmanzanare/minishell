/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:45:50 by vde-prad          #+#    #+#             */
/*   Updated: 2022/11/18 17:41:15 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../pipex.h"

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
	ft_putstr_fd("Error: command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	exit(127);
}

char	*ft_getpath(char **ep, char *cmd)
{
	unsigned int	i;
	char			*pathline;
	char			**paths;

	paths = NULL;
	i = 0;
	while (ep[i])
	{
		pathline = ft_strnstr(ep[i], "PATH", 5);
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
