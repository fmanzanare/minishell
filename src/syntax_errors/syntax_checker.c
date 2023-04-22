#include "../../includes/minishell.h"

/**
 * Checks if the received char is a semicolon or a backslash.
 * @param c current char.
 * @param *qmark quotation marks flags array.
*/
static int	semicol_backsl_chkr(char c, int *qmark)
{
	if (c == ';' && !qmark[0] && !qmark[1])
		return (1);
	else if (c == '\\' && !qmark[0] && !qmark[1])
		return (1);
	else
		return (0);
}

/**
 * Checks if the received char and the next are pipes or redirections.
 * @param c current char.
 * @param c_plus next char.
 * @param *qmark_flag quotation marks flags array.
 * @param *idx current index to be modified if needed.
 * @return 1 for redirections, 2 for pipe, 0 for any other char.
*/
static int	check_p_r(char c, char c_plus, int *qmark_flag, int *idx)
{
	if (c == '|' && !qmark_flag[0] && !qmark_flag[1])
		return (2);
	else if (c == '>' && c_plus != '>' && !qmark_flag[0] && !qmark_flag[1])
		return (1);
	else if (c == '<' && c_plus != '<' && !qmark_flag[0] && !qmark_flag[1])
		return (1);
	else if (c == '<' && c_plus == '<' && !qmark_flag[0] && !qmark_flag[1])
	{
		(*idx)++;
		return (1);
	}
	else if (c == '>' && c_plus == '>' && !qmark_flag[0] && !qmark_flag[1])
	{
		(*idx)++;
		return (1);
	}
	return (0);
}

/**
 * Goes through the line to find syntax errors.
 * Syntax error examples:
 * 	"$> echo hola > | wc -l"
 * 	"$> echo hola >> | wc -l"
 * 	"$> cat < | wc -l"
 * 	"$> cat << | wc -l"
 * 	"$> $ARG='hola'; echo $ARG"
 * 	"$> echo \$"
 * If pipes, redirections or simbols are between quotation marks they are
 * not considered to be a syntax error.
 * @param *str line received from inputs.
 * @return char/token where the syntax error is found.
*/
static char	error_fdr(char *str)
{
	int	i;
	int	flag;
	int	qmark[2];

	i = 0;
	flag = 0;
	qmark[0] = 0;
	qmark[1] = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		qmark[0] = check_s_qmark(str[i], qmark[0]);
		qmark[1] = check_d_qmark(str[i], qmark[1]);
		if (check_p_r(str[i], str[i + 1], qmark, &i) == 1 && flag == 0)
			flag = 1;
		else if ((check_p_r(str[i], str[i + 1], qmark, &i) == 1 && flag == 1)
			|| (check_p_r(str[i], str[i + 1], qmark, &i) == 2 && flag == 1)
			|| (semicol_backsl_chkr(str[i], qmark)))
			return (str[i]);
		else
			flag = 0;
		i++;
	}
	return ('\0');
}

/**
 * Checks syntax error at the begining of the line.
 * example: "$> | echo hola" o "$>      | echo hola" o "$> <", etc.
 * if no errors are found, it calls "error_fdr" function.
 * @param *str line received from inputs.
 * @return char/token where the syntax error is found.
*/
char	syntax_checker(char *str)
{
	int	i;
	int	qmark[2];

	i = 0;
	qmark[0] = 0;
	qmark[1] = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '|')
		return ('|');
	else if (check_p_r(str[i], str[i + 1], qmark, &i) == 1)
	{
		i++;
		while (str[i] == ' ')
			i++;
		if (str[i] == '\0')
			return ('\n');
	}
	return (error_fdr(str));
}
