#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft_plus/libft.h"
# include <readline/readline.h>
# include <stdlib.h>

typedef struct s_inputs
{
	char			*line;
	char			**line_arr;
	struct t_inputs	*prev;
	struct t_inputs	*next;
}				t_inputs;

/* UTILS */
char	**command_spliter(char *str, char c);
void	ft_free_arr(char **arr);

#endif
