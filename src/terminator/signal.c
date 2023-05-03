
#include "../../includes/minishell.h"

/**
 * Auxiliar signal handler. Its used in case of new subprocesses are
 * created.
 * @param signal the numbeer of the signal received
*/
void	ft_procs_sig(int signal)
{
	(void)signal;
	rl_redisplay();
}

/**
 * It handles the signals input. In case of 'ctrl + C' is pressed,
 * it creater a new and clean prompt.
 * @param signal Its the number of the signal received
*/
void	ft_sig_handler(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	kill(0, SIGUSR1);
}

/**
 * It checks what readlines return. If it returns a NULL pointer
 * it terminates the process. If enter is pressed sending a null
 * character, a new line is printed.
 * @param inputs parser part structure
 * @return 1 if null character is received. O if nothing is true
*/
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

/**
 * It saves the stdout and stdin, waits the last process,
 * kills all the subprocesses
 * 
 * @param data executor part strcuture
 * @param i iterator index
*/
void	ft_antibreeder(t_pipe data, int i)
{	
	dup2(data.cpy_out, STDOUT_FILENO);
	close(data.cpy_out);
	dup2(data.cpy_in, STDIN_FILENO);
	close(data.cpy_in);
	if (data.childpid[i - 1] != -1)
		waitpid(data.childpid[i - 1], &data.status, 0);
	while (i-- > 0)
	{
		if (data.childpid[i] != -1)
			kill(data.childpid[i], SIGKILL);
	}
}
