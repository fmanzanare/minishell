/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-prad <vde-prad@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:03:43 by vde-prad          #+#    #+#             */
/*   Updated: 2023/03/19 21:33:55 by vde-prad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
//*********************** STANDARD LIBRARIES *********************************
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include "../../includes/libft_plus/libft.h"
//************************** DEFINITIONS *************************************
typedef struct s_argdata{
	int		fdin;
	int		fdout;
	int		*pp;
	char	**cmd;
	char	***full_cmd;
}	t_argdata;
//*************************** FUNCTIONS **************************************
void	ft_setdata(t_argdata *pdata, char	**av, int ac);
char	*ft_getpath(char **ep, char *cmd);
#endif
