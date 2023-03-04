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

	if (argc != 1)
		return (1);
	if (!argv[0])
		return (1);
	while(1)
	{
		i = 0;
		inputs.line = readline(get_username(envp));
		inputs.line_arr = command_spliter(inputs.line, ' ');
		while (inputs.line_arr[i])
		{
			ft_printf("%s\n", inputs.line_arr[i]);
			i++;
		}
		add_history(inputs.line);
		ft_printf("%s\n", inputs.line);
	}
	free(inputs.line);
	return (0);
}
