#include "../../../includes/minishell.h"

int	ft_exit(t_inputs *inputs, t_pipe *data)
{
	(void)inputs;
	(void)data;
	ft_putstr_fd("exit\n", 1);
	exit(0);
}
