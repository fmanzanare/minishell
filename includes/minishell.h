#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft_plus/libft.h"
# include <readline/readline.h>
# include <stdlib.h>

typedef struct s_args
{
	char 			*cmd_line;
	char 			**cmd_arr;
	char 			*cmd_path;
	char 			*cmd_argv;
	struct s_args	*next;
	struct s_args	*prev;
}				t_args;

typedef struct s_inputs
{
	char			*line;
	char			**line_splited;
	t_args			*args;
}				t_inputs;

/* UTILS */
char		**command_spliter(char *str, char c);
void		ft_free_arr(char **arr);
t_args		*create_node(char *cmd_line);

#endif
