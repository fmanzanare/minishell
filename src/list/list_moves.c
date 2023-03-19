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
