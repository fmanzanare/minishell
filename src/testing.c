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

int	main(int argc, char **argv, char **envp)
{
	t_inputs	inputs;
	int			i;
	int			j;

	if (argc != 1)
		return (1);
	if (!argv[0])
		return (1);
	while(1)
	{
		i = 0;
		inputs.line = readline(get_username(envp));
		inputs.line_splited = ft_split(inputs.line, '|');
		fill_command_lines(&inputs.args, inputs.line_splited);
		run_to_head(&inputs.args);
		while (inputs.args)
		{
			j = 0;
			ft_printf("%s\n", inputs.args->cmd_line);
			ft_printf("Splited:\n");
			while (inputs.args->cmd_arr[j])
			{
				ft_printf("%d: %s\n", j, inputs.args->cmd_arr[j]);
				j++;
			}
			ft_printf("\n");
			if (!inputs.args->next)
				break;
			inputs.args = inputs.args->next;
		}
		add_history(inputs.line);
		free_list(&inputs.args);
		ft_free_arr(inputs.line_splited);
	}
	free(inputs.line);
	return (0);
}
