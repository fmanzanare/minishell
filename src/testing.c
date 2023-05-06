#include "../includes/minishell.h"

// FUNCION DE TESTING -> Imprime todo el contenido de INPUTS
void	print_inputs(t_inputs *inputs)
{
	int	j;

	while (inputs->args)
	{
		ft_printf("%s\n", inputs->args->cmd_line);
		ft_printf("Pipe flag: %d\n", inputs->args->pipe_flag);
		ft_printf("Input Redir flag: %d\n", inputs->args->ired_flag);
		ft_printf("Output Redir flag: %d\n", inputs->args->ored_flag);
		ft_printf("Append Redir flag: %d\n", inputs->args->app_flag);
		ft_printf("Heredoc Redir flag: %d\n", inputs->args->hd_flag);
		ft_printf("LINE SPLITED\n");
		j = 0;
		while (inputs->line_splited[j])
		{
			ft_printf("%d: %s\n", j, inputs->line_splited[j]);
			j++;
		}
		ft_printf("-------------------\n");
		ft_printf("Splited:\n");
		j = 0;
		while (inputs->args->cmd_split[j])
		{
			ft_printf("%d: %s\n", j, inputs->args->cmd_split[j]);
			j++;
		}
		ft_printf("-------------------\n");
		j = 0;
		while (inputs->args->cmd_arr[j])
		{
			ft_printf("%d: %s\n", j, inputs->args->cmd_arr[j]);
			j++;
		}
		if (inputs->args->inf)
		{
			j = 0;
			while (inputs->args->inf[j])
			{
				ft_printf("Infile: %s\n", inputs->args->inf[j]);
				j++;
			}
			ft_printf("FLAGS\n");
			j = 0;
			while (j < inputs->args->inf_len)
			{
				ft_printf("Infile flag: %d\n", inputs->args->inf_flags[j]);
				j++;
			}
		}
		if (inputs->args->outf)
		{
			j = 0;
			while (inputs->args->outf[j])
			{
				ft_printf("Outfile: %s\n", inputs->args->outf[j]);
				j++;
			}
			ft_printf("FLAGS\n");
			j = 0;
			while (j < inputs->args->outf_len)
			{
				ft_printf("Outfile flag: %d\n", inputs->args->outf_flags[j]);
				j++;
			}
		}
		if (inputs->args->inf_len)
			ft_printf("Infiles len: %d\n", inputs->args->inf_len);
		ft_printf("\n");
		if (!inputs->args->next)
			break ;
		inputs->args = inputs->args->next;
	}
	run_to_head(&inputs->args);
}

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
	char	*aux;

	aux = NULL;
	while (!ft_strnstr(*envp, "USER=", 5))
		envp++;
	ret = ft_substr(*envp, 5, envp[0][5]);
	aux = ret;
	ret = ft_strjoin(ret, " $> ");
	free(aux);
	return (ret);
}

static int	check_issues(t_inputs *inputs, char *user)
{
	if (ft_check_rl(inputs) || syntax_mngr(inputs->raw)
		|| is_blank_line(inputs->raw))
	{
		add_history(inputs->raw);
		free(inputs->raw);
		free(user);
		return (1);
	}
	return (0);
}

static void	minishell_loop(t_inputs *inputs, t_pipe *data, char **envp)
{
	char	*user;

	while (1)
	{
		inputs->line = NULL;
		user = get_username(envp);
		inputs->raw = readline(user);
		if (check_issues(inputs, user))
			continue ;
		parser(inputs, data);
		print_inputs(inputs); // FUNCIÓN DE TESTING -> Imprime el contenido de INPUTS
		inputs->exst = ft_terminator(inputs, data);
		free_list(&inputs->args);
		free(inputs->pipes_redir);
		ft_free_arr(inputs->line_splited);
		free(inputs->line);
		free(user);
	}
}

// FUNCION DE TESTING -> Comprueba los leaks del programa.
void	leaks()
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_inputs	inputs;
	t_pipe		data;

	atexit(leaks); // FUNCIÓN DE TESTING -> Comprueba los leaks del programa
	(void)argc;
	(void)argv;
	inputs.exst = 0;
	ft_init_terminator(envp, &data);
	minishell_loop(&inputs, &data, envp);
	return (0);
}
