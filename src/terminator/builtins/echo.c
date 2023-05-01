
#include "../../../includes/minishell.h"
/**
 * Write arguments to the standard output 
 * @param flag It checks if the flag '-n' was passed
 * @param i iterator index
*/
int	ft_echo(t_inputs *inputs)
{
	int	flag;
	int	i;

	i = 1;
	flag = 1;
	if (inputs->args->cmd_arr[i]
		&& !ft_strncmp(inputs->args->cmd_arr[i], "-n", ft_strlen("-n")))
	{
		flag = 0;
		i++;
	}
	while (inputs->args->cmd_arr[i])
	{
		ft_putstr_fd(inputs->args->cmd_arr[i], 1);
		if (inputs->args->cmd_arr[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (flag)
		ft_putstr_fd("\n", 1);
	return (-1);
}
