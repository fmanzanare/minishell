
#include "../../includes/minishell.h"

void	ft_procs_sig(int signal)
{
	(void)signal;
	rl_redisplay();
}

void	ft_sig_handler(int signal)
{
	(void)signal;
	rl_on_new_line();
	ft_putstr_fd("\n", 1);
	kill(0, SIGUSR1);
}

int	ft_check_rl(t_inputs *inputs)
{
	if (inputs->line == NULL)
		exit(0);
	if (inputs->line[0] == '\0')
	{
		rl_on_new_line();
		return (1);
	}
	return (0);
}

void	ft_antibreeder(t_pipe data, int i)
{	
	dup2(data.cpy_out, STDOUT_FILENO);
	dup2(data.cpy_in, STDIN_FILENO);
	close(data.cpy_out);
	close(data.cpy_in);
	if (data.childpid[i - 1] != -1)
		waitpid(data.childpid[i - 1], &data.status, 0);
	while (i-- > 0)
	{
		if (data.childpid[i] != -1)
			kill(data.childpid[i], SIGKILL);
	}
}
