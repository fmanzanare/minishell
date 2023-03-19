/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setdata.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:48:26 by vde-prad          #+#    #+#             */
/*   Updated: 2023/03/19 22:19:10 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

//parser the cmd name, flags and cmd arguments in a double char pointer
static void	ft_parserarg(char	**av, t_argdata *pdata, int ac)
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	pdata->full_cmd = malloc(sizeof(char ***));
	pdata->cmd = malloc(sizeof(char **));
	while (i <= ac - 2)
	{
		if (av[i][0] != 0)
		{
			pdata->full_cmd[j] = ft_split(av[i], ' ');
			pdata->cmd[j] = ft_strdup(pdata->full_cmd[j][0]);
			i++;
			j++;
		}
		else
		{
			ft_putstr_fd("Error: argument(s) empty\n", 2);
			exit(127);
		}
	}
}

//set fdin, fdout, pp, cmd and options in data structure
void	ft_setdata(t_argdata *pdata, char	**av, int ac)
{
	if (!access(av[1], F_OK | R_OK))
		pdata->fdin = open(av[1], O_RDONLY);
	else
	{
		ft_putstr_fd("Error: input file innaccesible\n", 2);
		exit(127);
	}
	pdata->fdout = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pdata->fdout < 0)
	{
		ft_putstr_fd("Error: output file innaccesible\n", 2);
		exit(127);
	}
	if (pipe(pdata->pp) == 1)
	{
		ft_putstr_fd("Error: pipe\n", 2);
		exit(127);
	}
	ft_parserarg(av, pdata, ac);
}

int	main(int ac, char **av)
{
	t_argdata	data;
	int			i = 0;
	int			j = 0;

	printf("ac = %d\n", ac);
	ft_parserarg(av, &data, ac);
	while (i < ac - 3)
	{
		printf("cmd : %s\n", data.cmd[i]);
		while (data.full_cmd[i][j])
			printf("full_cmd : %s\n", data.full_cmd[i][j++]);
		j = 0;
		i++;
	}
}