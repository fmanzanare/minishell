#include "../../includes/minishell.h"

/**
 * Checks if a simple quotation mark is opened or closed.
 * @param c Char to be checked.
 * @param qmark_flag Flag to be returned.
 * @return 1 if quotation mark is opened and 0 if it is closed.
*/
static int	check_s_qmark(char c, int qmark_flag)
{
	if (c == '\'' && !qmark_flag)
		qmark_flag = 1;
	else if (c == '\'' && qmark_flag)
		qmark_flag = 0;
	return (qmark_flag);
}

/**
 * Checks if a double quotation mark is opened or closed.
 * @param c Char to be checked.
 * @param qmark_flag Flag to be returned.
 * @return 1 if quotation mark is opened and 0 if it is closed.
*/
static int	check_d_qmark(char c, int qmark_flag)
{
	if (c == '\"' && !qmark_flag)
		qmark_flag = 1;
	else if (c == '\"' && qmark_flag)
		qmark_flag = 0;
	return (qmark_flag);
}

/**
 * Mesures the lenght of the new string, countin pipes "|"
 * and redirections "< or >".
 * @param *str String to go through.
 * @return Length of the new string.
*/
static int	pipes_redirs_len(char *str)
{
	int	i;
	int	ret;
	int	s_qmark_flag;
	int	d_qmark_flag;

	i = 0;
	ret = 0;
	s_qmark_flag = 0;
	d_qmark_flag = 0;
	while (str[i])
	{
		s_qmark_flag = check_s_qmark(str[i], s_qmark_flag);
		d_qmark_flag = check_d_qmark(str[i], d_qmark_flag);
		if (str[i] == '|' && !d_qmark_flag && !s_qmark_flag)
			ret++;
		else if (str[i] == '>' && str[i + 1] != '>' && !d_qmark_flag
			&& !s_qmark_flag)
			ret++;
		else if (str[i] == '<' && str[i + 1] != '<' && !d_qmark_flag
			&& !s_qmark_flag)
			ret++;
		i++;
	}
	return (ret);
}

/**
 * Checks if the received char is a pipe "|" or a redirection "< or >"
 * @param c Current char in the full line (pipes_redir_stringer function).
 * @param c_plus Next char in the full line.
 * @param s_qmark_flag Flag to verify simple quotation marks.
 * @param d_qmark_flag Flag to verify double quotation marks.
*/
static int	check_p_r(char c, char c_plus, int s_qmark_flag, int d_qmark_flag)
{
	if (c == '|' && !s_qmark_flag && !d_qmark_flag)
		return (1);
	else if (c == '>' && c_plus != '>' && !s_qmark_flag && !d_qmark_flag)
		return (1);
	else if (c == '<' && c_plus != '<' && !s_qmark_flag && !d_qmark_flag)
		return (1);
	else
		return (0);
}

/**
 * Builds the string that contains the pipes and redirections.
 * The string is saved in "inputs->pipes_redir" variable.
 * @param *inputs Pointer to "inputs" struct.
*/
void	pipes_redirs_stringer(t_inputs *inputs)
{
	int		d_qmark;
	int		s_qmark;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s_qmark = 0;
	d_qmark = 0;
	inputs->pipes_redir = malloc(sizeof(char) * pipes_redirs_len(inputs->line));
	while (inputs->line[j])
	{
		s_qmark = check_s_qmark(inputs->line[j], s_qmark);
		d_qmark = check_d_qmark(inputs->line[j], d_qmark);
		if (check_p_r(inputs->line[j], inputs->line[j + 1], s_qmark, d_qmark))
		{
			inputs->pipes_redir[i] = inputs->line[j];
			i++;
		}
		j++;
	}
	inputs->pipes_redir[i] = '\0';
}

// TEMPORARY FUNCTION TO VERIFY THAT STRING IS BEING BUILT CORRECTLY.
void	print_pipes_redirs_str(t_inputs *inputs)
{
	int		i;

	i = 0;
	pipes_redirs_stringer(inputs);
	while (inputs->pipes_redir[i])
	{
		ft_printf("%c", inputs->pipes_redir[i]);
		i++;
	}
	ft_printf("\n");
}
