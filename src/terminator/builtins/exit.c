#include "../../../includes/minishell.h"

static int	nodigit_fdr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

static int	ft_atoi_exit(char *str)
{
	long int			num;
	int					sign;
	int					num_str;

	num_str = nodigit_fdr(str);
	sign = 1;
	num = 0;
	if (!*str)
		return (0);
	while (ft_isspecialchar(*str))
		str++;
	if (ft_issign(*str) == -1)
		sign = -1;
	if (ft_issign(*str))
		str++;
	while (*str && ft_isdigit(*str))
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	if (!num_str || num < INT_MIN || num > INT_MAX)
		return (255);
	num *= sign;
	return ((int)num);
}

int	ft_exit(t_inputs *inputs)
{
	int		len;
	int		exit_num;

	len = array_len(inputs->args->cmd_arr);
	if (len > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		return (-1);
	}
	else if (len == 2)
	{
		exit_num = ft_atoi_exit(inputs->args->cmd_arr[1]);
		if (exit_num == 255)
		{
			printf("minishell: exit: %s: numeric argument required\n",
				inputs->args->cmd_arr[1]);
			exit(exit_num);
		}
		ft_putstr_fd("exit\n", 1);
		if (exit_num < 0)
			exit(256 + exit_num);
		exit(exit_num);
	}
	ft_putstr_fd("exit\n", 1);
	exit(0);
}
