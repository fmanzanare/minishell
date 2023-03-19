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
	int				pipe_flag;
	int				red_flag;
	struct s_args	*next;
	struct s_args	*prev;
}				t_args;

typedef struct s_inputs
{
	char			*line;
	char			**line_splited;
	int				lenght;
	char			*pipes_redir;
	t_args			*args;
}				t_inputs;

/*** UTILS ***/
// free_fts.c
void	ft_free_arr(char **arr);
void	free_list(t_args **args);
// command_spliter.c
char	**command_spliter(char *str, char c);
// inputs_spliter.c
int 	input_size(char **line_splited);
// pipes_and_redirs.c
void	pipes_redirs_stringer(t_inputs *inputs);
void	print_pipes_redirs_str(t_inputs *inputs); //For testing.

/** LIST **/
// list_utils.c
char	*ft_trim(char *str, int node, int input_len);
// list_moves.c
void	run_to_head(t_args **args);
void	run_to_tail(t_args **args);
// list_filler.c
void	fill_command_lines(t_args **args, char **line_splited, t_inputs *inputs);

#endif
