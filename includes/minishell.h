#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft_plus/libft.h"
# include <readline/readline.h>

typedef struct s_inputs
{
	char			*line;
	char			**line_arr;
	struct t_inputs	*prev;
	struct t_inputs	*next;
}				t_inputs;

#endif
