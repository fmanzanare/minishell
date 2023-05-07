#include "../../../includes/minishell.h"

int	ft_cd(char **cmd_arr, t_pipe *data)
{
	char	old_pwd[512];
	char	current_pwd[512];
	char	*complete_var;

	getcwd(old_pwd, 512);
	complete_var = ft_strjoin("OLDPWD=", old_pwd);
	if (!cmd_arr[1])
		cmd_arr[1] = ft_strdup("/Users/vde-prad");
	if (chdir(cmd_arr[1]) == -1)
	{
		data->built_st = 1;	
		ft_putstr_fd("cd : ",2);
		ft_putstr_fd(cmd_arr[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(complete_var);
		return (-1);
	}
	ft_set_variable(complete_var, data);
	getcwd(current_pwd, 512);
	free(complete_var);
	complete_var = ft_strjoin("PWD=", current_pwd);
	ft_set_variable(complete_var, data);
	free(complete_var);
	return (-1);
}
