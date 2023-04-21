
#include "../../includes/minishell.h"

static void	ft_sig_handler(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	ft_check_rl(t_inputs *inputs)
{
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	if (inputs->line == NULL)
		exit(0);
	if (inputs->line[0] == '\0')
	{
		rl_on_new_line();
		return (1);
	}
	return (0);
}
