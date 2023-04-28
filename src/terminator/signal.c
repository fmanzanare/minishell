
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

void	ft_setterm(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
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
	waitpid(data.childpid[i - 1], &data.status, 0);
	while (i-- > 0)
		kill(data.childpid[i], SIGKILL);
}
