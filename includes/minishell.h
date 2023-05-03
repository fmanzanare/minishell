#ifndef MINISHELL_H
# define MINISHELL_H

//*********************** STANDARD LIBRARIES *********************************//
# include "./libft_plus/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
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
	char			*infile;
	char			*delim;
	char			*outfile;
	int				pipe_flag;
	int				ored_flag;
	int				ired_flag;
	int				app_flag;
	int				hd_flag;
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

typedef struct s_env
{
	char			*line;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

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
// free_fts.c
void	ft_free_arr(char **arr);
void	free_list(t_args **args);
// command_spliter.c
char	**command_spliter(char *str, char c);
// inputs_spliter.c
int		input_size(char **line_splited);
// pipes_and_redirs.c
void	pipes_redirs_stringer(t_inputs *inputs);
void	print_pipes_redirs_str(t_inputs *inputs); //For testing.
// qmarks_fts.c
int		check_s_qmark(char c, int qmark_flag);
int		check_d_qmark(char c, int qmark_flag);

//** LIST **//
// list_moves.c
void	run_to_head(t_args **args);
void	run_to_tail(t_args **args);
// list_filler.c
void	fill_command_lines(t_args **args, char **line_splited,
			t_inputs *inputs);
// iofiles_fdr.c
void	iofiles_fdr(t_args *node);
// cmd_arrayer.c
void	cmd_arrayer(t_args *node);

//** SYNTAX_ERRORS **//
// syntax_checker.c
char	syntax_checker(char *str);

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
void	ft_antibreeder(t_pipe data, int i);
// echo.c
int		ft_echo(t_inputs *inputs);
int		ft_cd(t_inputs *inputs);
int		ft_env(t_pipe *data);
// pwd.c
int		ft_pwd(t_pipe *data);
// export.c
int		ft_export(t_inputs *inputs, t_pipe *data);
int		ft_find_var(char *var, t_pipe *data, t_env **target);
int		ft_check_alpha(char *arg, int i, const char *type);
// unset.c
int		ft_unset(t_inputs *inputs, t_pipe *data);
// utils.c
void	ft_init_terminator(char **envp, t_pipe *data);
t_env	*ft_new_node(char *line);
#endif
