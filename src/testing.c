#include "../includes/minishell.h"

static char	*get_username(char **envp)
{
	char	*ret;

	while(!ft_strnstr(*envp, "USER=", 5))
		envp++;
	ret = ft_substr(*envp, 5, envp[0][5]);
	ret = ft_strjoin(ret, " $> ");
	return (ret);
}

int	arr_len (char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	run_to_head(t_args **args)
{
	while ((*args)->prev)
		*args = (*args)->prev;
}

int	main(int argc, char **argv, char **envp)
{
	t_inputs	inputs;
	int			i;

	if (argc != 1)
		return (1);
	if (!argv[0])
		return (1);
	i = 0;
	while(1)
	{
		inputs.line = readline(get_username(envp));
		inputs.line_splited = ft_split(inputs.line, '|');
		while (inputs.line_splited[i])
		{
			if (i == 0)
				inputs.args = create_node(inputs.line_splited[i]);
			else
			{
				inputs.args->next = create_node(inputs.line_splited[i]);
				inputs.args->next->prev = inputs.args;
				inputs.args = inputs.args->next;
			}
			i++;
		}
		run_to_head(&inputs.args);
		while (inputs.args)
		{
			ft_printf("%s\n", inputs.args->cmd_line);
			inputs.args = inputs.args->next;
		}
		add_history(inputs.line);
		//ft_printf("%s\n", inputs.line);
	}
	free(inputs.line);
	return (0);
}
