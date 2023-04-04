#include "../includes/minishell.h"

/**
 * Checks if a syntax error is found and prints the error message.
 * @param *str line received from inputs.
 * @return 1 if a syntax error is found, 0 if no errors are found.
*/
static int	syntax_mngr(char *str)
{
	char	token;

	token = syntax_checker(str);
	if (token != '\n' && token)
	{
		ft_printf("minishell: syntax error near unexpected token \'%c\'\n",
			token);
		return (1);
	}
	else if (token == '\n')
	{
		ft_printf("minishell: syntax error near unexpected token \'newline\'\n");
		return (1);
	}
	return (0);
}

/**
 * Gets the username from the enviroment variable USER.
 * @param **envp enviroment variables.
 * @return string with the username.
*/
static char	*get_username(char **envp)
{
	char	*ret;

	while (!ft_strnstr(*envp, "USER=", 5))
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
	while (1)
	{
		i = 0;
		inputs.line = readline(get_username(envp));
		if (syntax_mngr(inputs.line))
		{
			add_history(inputs.line);
			continue ;
		}
		pipes_redirs_stringer(&inputs);
		print_pipes_redirs_str(&inputs);
		inputs.line_splited = ft_split(inputs.line, '|');
		inputs.lenght = input_size(inputs.line_splited);
		fill_command_lines(&inputs.args, inputs.line_splited, &inputs);
		run_to_head(&inputs.args);
		while (inputs.args)
		{
			j = 0;
			ft_printf("%s\n", inputs.args->cmd_line);
			ft_printf("Pipe flag: %d\n", inputs.args->pipe_flag);
			ft_printf("Input Redir flag: %d\n", inputs.args->ired_flag);
			ft_printf("Output Redir flag: %d\n", inputs.args->ored_flag);
			ft_printf("Append Redir flag: %d\n", inputs.args->app_flag);
			ft_printf("Heredoc Redir flag: %d\n", inputs.args->hd_flag);
			ft_printf("Splited:\n");
			while (inputs.args->cmd_arr[j])
			{
				ft_printf("%d: %s\n", j, inputs.args->cmd_arr[j]);
				j++;
			}
			ft_printf("\n");
			if (!inputs.args->next)
				break ;
			inputs.args = inputs.args->next;
		}
		add_history(inputs.line);
		free_list(&inputs.args);
		ft_free_arr(inputs.line_splited);
	}
	free(inputs.line);
	return (0);
}
