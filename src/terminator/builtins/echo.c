
#include "../../../includes/minishell.h"

int	ft_echo(t_inputs *inputs)
{
	int	flag;
	int	i;

	i = 1;
	flag = 1;
	if (inputs->args->cmd_arr[i]
		&& !ft_strncmp(inputs->args->cmd_arr[i], "-n", ft_strlen("-n")))
		flag = 0;
	while (inputs->args->cmd_arr[++i])
		ft_putstr_fd(inputs->args->cmd_arr[i], 1);
	if (flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
