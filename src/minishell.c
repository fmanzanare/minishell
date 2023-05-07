/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:14:28 by fmanzana          #+#    #+#             */
/*   Updated: 2023/05/07 17:15:50 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (inputs->raw[0] != '\0')
			add_history(inputs->raw);
		free(inputs->raw);
		free(user);
		return (1);
	}
	return (0);
}

static void	minishell_loop(char **envp)
{
	t_inputs	inputs;
	t_pipe		data;
	char		*user;

	inputs.exst = 0;
	ft_init_terminator(envp, &data);
	while (1)
	{
		inputs.line = NULL;
		user = get_username(envp);
		inputs.raw = readline(user);
		if (check_issues(&inputs, user))
			continue ;
		parser(&inputs, &data);
		inputs.exst = ft_terminator(&inputs, &data);
		free_list(&inputs.args);
		free(inputs.pipes_redir);
		ft_free_arr(inputs.line_splited);
		free(inputs.line);
		free(user);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	minishell_loop(envp);
	return (0);
}
