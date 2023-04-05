#include"../../includes/minishell.h"

/**
 * Checks if a simple quotation mark is opened or closed.
 * @param c Char to be checked.
 * @param qmark_flag Flag to be returned.
 * @return 1 if quotation mark is opened and 0 if it is closed.
*/
int	check_s_qmark(char c, int qmark_flag)
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
int	check_d_qmark(char c, int qmark_flag)
{
	if (c == '\"' && !qmark_flag)
		qmark_flag = 1;
	else if (c == '\"' && qmark_flag)
		qmark_flag = 0;
	return (qmark_flag);
}
