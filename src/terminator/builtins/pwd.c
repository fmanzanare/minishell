#include "../../../includes/minishell.h"

/**
 * It prints the working directry name
 * @param data struct with the neccessary data 
 * @return It returns 
*/
int	ft_pwd(t_pipe *data)
{
	printf("%s\n", getcwd(data->pwd, 512));
	return (-1);
}
