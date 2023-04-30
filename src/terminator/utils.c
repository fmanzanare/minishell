#include "../../includes/minishell.h"

static t_env	*ft_new_node(char *line)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	node->line = ft_strdup(line);
	return (node);
}

void	ft_init_terminator(char	**envp, t_pipe *data)
{
	t_env			*aux;
	struct termios	t;
	int				i;

	i = 0;
	data->env = ft_new_node(envp[i]);
	aux = data->env;
	while (envp[++i])
	{
		aux->next = ft_new_node(envp[i]);
		aux = aux->next;
	}
	aux->next = NULL;
	signal(SIGINT, ft_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGUSR1, ft_procs_sig);
	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}
