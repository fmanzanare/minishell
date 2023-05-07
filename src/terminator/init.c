
#include "../../includes/minishell.h"

static void    ft_init_envlst(char **envp, t_pipe *data)
{
	t_env			*aux;
	t_env			*tmp;
	int				i;

    data->envp = malloc((array_len(envp) + 1) * sizeof(char *));
    if (!data->envp)
        exit(127);
	i = 0;
	data->env = ft_new_node(envp[i]);
    data->envp[i] = ft_strdup(envp[i]);
	aux = data->env;
	aux->prev = NULL;
	while (envp[++i])
	{
		tmp = aux;
		aux->next = ft_new_node(envp[i]);
        data->envp[i] = ft_strdup(envp[i]);
		aux = aux->next;
		aux->prev = tmp;
	}
	aux->next = NULL;
    data->envp[i] = NULL;
}

/**
 * It initializes the main data structure variables, signal input
 * and terminal set.
 * @param envp environment variables
 * @param data own structure
 * @param aux auxiliar 't_env' variable to set the linked list
 * @param t structure of type of 'termios'
 * @param i iterator index
*/
void	ft_init_terminator(char	**envp, t_pipe *data)
{
	struct termios	t;

    data->built_st = 0;
    ft_init_envlst(envp, data);
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGUSR1, ft_procs_sig);
	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}