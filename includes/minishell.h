#ifndef MINISHELL_H
# define MINISHELL_H

//*********************** STANDARD LIBRARIES *********************************//
# include "./libft_plus/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <limits.h>
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>

//************************** DEFINITIONS *************************************//
typedef struct s_args
{
	char			*cmd_line;
	char			**cmd_split;
	char			**cmd_arr;
	char			*cmd_path;
	char			**inf;
	int				*inf_flags;
	int				inf_len;
	char			**outf;
	int				*outf_flags;
	int				outf_len;
	int				pipe_flag;
	int				ored_flag;
	int				ired_flag;
	int				app_flag;
	int				hd_flag;
	struct s_args	*next;
	struct s_args	*prev;
}	t_args;

typedef struct s_inputs
{
	char			*raw;
	char			*line;
	char			**line_splited;
	int				exst;
	int				lenght;
	char			*pipes_redir;
	t_args			*args;
}	t_inputs;

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_pipe
{
	int		*childpid;
	int		cpy_out;
	int		cpy_in;
	int		status;
	int		fdin;
	int		fdout;
	int		pp[2];
	char	pwd[512];
	char	**envp;
	t_env	*env;
}	t_pipe;

//*************************** FUNCTIONS **************************************

//*** UTILS ***//
// inputs_utils.c
int		input_size(char **line_splited);
int		is_blank_line(char *line);
// pipes_and_redirs.c
void	pipes_redirs_stringer(t_inputs *inputs);
void	print_pipes_redirs_str(t_inputs *inputs); //For testing.
// qmarks_fts.c
int		check_s_qmark(char c, int qmark_flag);
int		check_d_qmark(char c, int qmark_flag);
// deep_spliter.c
char	**deep_spliter(char *s, char c);
//** FREE_FTS **//
// free_utils.c
void	ft_free_arr(char **arr);
void	free_list(t_args **args);

//** LIST **//
// list_moves.c
void	run_to_head(t_args **args);
void	run_to_tail(t_args **args);
// list_filler.c
void	fill_command_lines(t_args **args, char **line_splited,
			t_inputs *inputs);
// iofiles_fdr.c
void	iofiles_fdr(t_args *node);
// iofiles_utils.c
int		files_len(t_args *node, int *i);
// infiles_utils.c
void	infiles_mngr(t_args *node, int *qmarks);
void	infiles_flags_filler(t_args *node);
// cmd_arrayer.c
void	cmd_arrayer(t_args *node, int i, int j);
// cmd_arrayer_utils.c
char	*cmdjoin(char *str);
int		array_len(char **arr);
// parser.c
void	parser(t_inputs *inputs, t_pipe *data);

//** SYNTAX_ERRORS **//
// syntax_checker.c
char	syntax_checker(char *str);

//* EXPANDER *//
// expander.c
void	ft_expander(t_inputs *inputs, t_env *env);
// expander_utils.c
char	*ft_charjoin(char *s, char c);

//** PIPE **//
// redirections.c
void	ft_setdata(t_inputs *inputs, t_pipe *data);
// parserpath.c
char	*ft_getpath(char **ep, char *cmd);
// terminator.c
int		ft_terminator(t_inputs *inputs, t_pipe *data);
// signal.c
int		ft_check_rl(t_inputs *inputs);
void	ft_sig_handler(int signal);
void	ft_procs_sig(int signal);
void	ft_antibreeder(t_pipe *data, int i);
// echo.c
int		ft_echo(t_inputs *inputs);
// env.c
int		ft_env(t_pipe *data);
// pwd.c
int		ft_pwd(t_pipe *data);
// export.c
int		ft_export(char **cmd_arr, t_pipe *data);
int		ft_find_var(char *var, t_pipe *data, t_env **target);
int		ft_check_alpha(char *arg, int i, const char *type);
void	ft_set_variable(char *arg, t_pipe *data);
// unset.c
int		ft_unset(t_inputs *inputs, t_pipe *data);
// exit.c
// TODO: free memory of structs
int		ft_exit(t_inputs *inputs);
// cd.c
int		ft_cd(char **cmd_arr, t_pipe *data);
// utils.c
void	ft_init_terminator(char **envp, t_pipe *data);
t_env	*ft_new_node(char *line);
#endif
