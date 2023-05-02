#include "../../includes/minishell.h"

/**
 * Checks if the char and next char of a string is a redirection and
 * modifies the received index of the string.
 * @param c current char of the string.
 * @param c_plus next char of the string.
 * @param *qmark_flag checks if simple or double quotation marks ara closed.
 * @param *size pointer to the new string size.
*/
static void	check_redirs(char c, char c_plus, int *qmark_flag, int *size)
{
	if (c == '>' && c_plus != '>' && !qmark_flag[0]
		&& !qmark_flag[1])
			(*size) += 2;
	else if (c == '<' && c_plus != '<' && !qmark_flag[0]
		&& !qmark_flag[1])
			(*size) += 2;
	else if (c == '>' && c_plus == '>' && !qmark_flag[0]
		&& !qmark_flag[1])
			(*size) += 3;
	else if (c == '<' && c_plus == '<' && !qmark_flag[0]
		&& !qmark_flag[1])
			(*size) += 3;
}

/**
 * Mesures the lenght of the new string, countin pipes "|"
 * and redirections "<", ">", "<<" or ">>".
 * @param *str String to go through.
 * @return Length of the new string.
*/
static int	pipes_redirs_len(char *str)
{
	int	i;
	int	ret;
	int	qmark_flag[2];

	i = 0;
	ret = 0;
	qmark_flag[0] = 0;
	qmark_flag[1] = 0;
	while (str[i])
	{
		qmark_flag[0] = check_s_qmark(str[i], qmark_flag[0]);
		qmark_flag[1] = check_d_qmark(str[i], qmark_flag[1]);
		if (str[i] == '|' && !qmark_flag[0] && !qmark_flag[1])
			ret += 2;
		else
			check_redirs(str[i], str[i + 1], qmark_flag, &ret);
		i++;
	}
	return (ret);
}

/**
 * Checks if the received char is a pipe "|" or a redirection.
 * @param c Current char in the full line (pipes_redir_stringer function).
 * @param c_plus Next char in the full line.
 * @param s_qmark_flag Flag to verify simple quotation marks.
 * @param d_qmark_flag Flag to verify double quotation marks.
*/
static int	check_p_r(char c, char c_plus, int *qmark_flag)
{
	if (c == '|' && !qmark_flag[0] && !qmark_flag[1])
		return (1);
	else if (c == '>' && c_plus != '>' && !qmark_flag[0] && !qmark_flag[1])
		return (1);
	else if (c == '<' && c_plus != '<' && !qmark_flag[0] && !qmark_flag[1])
		return (1);
	else if (c == '>' && c_plus == '>' && !qmark_flag[0] && !qmark_flag[1])
		return (2);
	else if (c == '<' && c_plus == '<' && !qmark_flag[0] && !qmark_flag[1])
		return (2);
	else
		return (0);
}

/**
 * Builds the string that contains the pipes and redirections separated by ' '.
 * The string is saved in "inputs->pipes_redir" variable.
 * @param *inputs Pointer to "inputs" struct.
*/
void	pipes_redirs_stringer(t_inputs *inputs)
{
	int		qmark[2];
	int		i;
	int		j;

	i = 0;
	j = 0;
	qmark[0] = 0;
	qmark[1] = 0;
	inputs->pipes_redir = malloc(sizeof(char) * pipes_redirs_len(inputs->line));
	while (inputs->line[j])
	{
		qmark[0] = check_s_qmark(inputs->line[j], qmark[0]);
		qmark[1] = check_d_qmark(inputs->line[j], qmark[1]);
		if (check_p_r(inputs->line[j], inputs->line[j + 1], qmark) == 1)
		{
			inputs->pipes_redir[i] = inputs->line[j];
			inputs->pipes_redir[i + 1] = ' ';
			i += 2;
		}
		else if (check_p_r(inputs->line[j], inputs->line[j + 1], qmark) == 2)
		{
			inputs->pipes_redir[i] = inputs->line[j];
			inputs->pipes_redir[i + 1] = inputs->line[j + 1];
			inputs->pipes_redir[i + 2] = ' ';
			i += 3;
			j++;
		}
		j++;
	}
	inputs->pipes_redir[i] = '\0';
}
