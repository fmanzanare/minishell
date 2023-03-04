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

	if (argc != 1)
		return (1);
	if (!argv[0])
		return (1);
	while(1)
	{
		inputs.line = readline(get_username(envp));
		add_history(inputs.line);
		ft_printf("%s\n", inputs.line);
	}
	free(inputs.line);
	return (0);
}
