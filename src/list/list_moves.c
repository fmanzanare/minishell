/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_moves.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:09:19 by fmanzana          #+#    #+#             */
/*   Updated: 2023/05/07 17:09:20 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Places the "args" struct pointer at the begining of the list.
 * @param **args Pointer to "args" struct
*/
void	run_to_head(t_args **args)
{
	while ((*args)->prev)
		*args = (*args)->prev;
}

/**
 * Places the "args" struct pointer at the end of the list.
 * @param **args Pointer to "args" struct
*/
void	run_to_tail(t_args **args)
{
	while ((*args)->next)
		*args = (*args)->next;
}
