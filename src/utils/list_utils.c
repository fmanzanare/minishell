#include "../../includes/minishell.h"

void	run_to_head(t_args **args)
{
	while ((*args)->prev)
		*args = (*args)->prev;
}

void	run_to_tail(t_args **args)
{
	while ((*args)->next)
		*args = (*args)->next;
}

char	*ft_trim(char *str, int first_node)
{
	int		len;
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 1;
	if (!first_node)
		j = 0;
	len = ft_strlen(str) - 1;
	res = malloc(sizeof(char *) * len);
	while (i < len)
	{
		res[i] = str[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

static t_args	*create_node(char *cmd_line, int first_node)
{
	t_args	*new;

	new = malloc(sizeof * new);
	new->cmd_line = ft_trim(cmd_line, first_node);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	fill_command_lines(t_args **args, char **line_splited)
{
	int		i;

	i = 0;
	while (line_splited[i])
	{
		if (i == 0)
			*args = create_node(line_splited[i], i);
		else
		{
			(*args)->next = create_node(line_splited[i], i);
			(*args)->next->prev = *args;
			*args = (*args)->next;
		}
		i++;
	}
}
