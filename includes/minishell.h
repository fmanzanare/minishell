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

/*** UTILS ***/
char		**command_spliter(char *str, char c);
// free_fts.c
void		ft_free_arr(char **arr);
void		free_list(t_args **args);
// list_utils.c
void		run_to_head(t_args **args);
void		run_to_tail(t_args **args);
void		fill_command_lines(t_args **args, char **line_splited);

#endif
