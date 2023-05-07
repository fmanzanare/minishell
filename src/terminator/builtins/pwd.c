/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:10:22 by fmanzana          #+#    #+#             */
/*   Updated: 2023/05/07 17:10:23 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/**
 * It prints the working directry name
 * @param data struct with the neccessary data
 * @return It returns
*/
int	ft_pwd(t_pipe *data)
{
	printf("%s\n", getcwd(data->pwd, 512));
	data->built_st = 0;
	return (-1);
}
