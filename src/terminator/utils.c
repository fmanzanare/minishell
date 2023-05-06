#include "../../includes/minishell.h"

/**
 * It creates a new node to fill the linked list
 * @param line value will set the node content
 * @param node
*/
t_env	*ft_new_node(char *line)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		exit(1);
	node->line = ft_strdup(line);
	return (node);
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
	t_env			*aux;
	t_env			*tmp;
	struct termios	t;
	int				i;

	i = 0;
	data->env = ft_new_node(envp[i]);
	aux = data->env;
	aux->prev = NULL;
	while (envp[++i])
	{
		tmp = aux;
		aux->next = ft_new_node(envp[i]);
		aux = aux->next;
		aux->prev = tmp;
	}
	aux->next = NULL;
	data->envp = envp;
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGUSR1, ft_procs_sig);
	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}
