#include "../../includes/minishell.h"

/**
 * Get the string to be saved into the array.
 * @param *s String to work with.
 * @param start Starting index.
 * @param end Index of the new string end.
*/
static char	*stringmkr(char *s, int start, int end)
{
	char	*wrd;
	int		i;

	i = 0;
	wrd = malloc((end - start + 1) * sizeof(char));
	if (!wrd)
		exit(1);
	while (start < end)
		wrd[i++] = s[start++];
	wrd[i] = '\0';
	return (wrd);
}

/**
 * Counts the number of words, that the final array will contain.
 * @param *s String to work with.
 * @param c Split char.
 * @return Number of words.
*/
static int	wordscntr(char *s, char c)
{
	int		i;
	int		flag;
	int		strs;
	int		qmarks[2];

	i = 0;
	flag = 0;
	strs = 0;
	qmarks[0] = 0;
	qmarks[1] = 0;
	while (s[i])
	{
		qmarks[0] = check_s_qmark(s[i], qmarks[0]);
		qmarks[1] = check_d_qmark(s[i], qmarks[1]);
		if (s[i] != c && flag == 0)
		{
			flag = 1;
			strs++;
		}
		else if (s[i] == c && !qmarks[0] && !qmarks[1])
			flag = 0;
		i++;
	}
	return (strs);
}

/**
 * Fills the array of string with the splited lines from the received string.
 * @param **dst Array to be filled and returned.
 * @param *s String to work with.
 * @param c Split char.
 * @param idx Index.
*/
static char	**split_arrayer(char **dst, char *s, char c, int idx)
{
	size_t	i;
	int		j;
	int		qmarks[2];

	i = 0;
	j = 0;
	qmarks[0] = 0;
	qmarks[1] = 0;
	while (i <= ft_strlen(s))
	{
		qmarks[0] = check_s_qmark(s[i], qmarks[0]);
		qmarks[1] = check_d_qmark(s[i], qmarks[1]);
		if (s[i] != c && idx < 0)
			idx = i;
		else if ((s[i] == c || i == ft_strlen(s)) && idx >= 0
			&& !qmarks[0] && !qmarks[1])
		{
			dst[j++] = stringmkr(s, idx, i);
			idx = -1;
		}
		i++;
	}
	dst[j] = 0;
	return (dst);
}

/**
 * Special split that checks the qmarks.
 * If split char is within qmarks, it is not splited.
 * @param *s String to work with.
 * @param c Split char.
 * @return Array of string, spliting the received string by c.
*/
char	**deep_spliter(char *s, char c)
{
	int		i;
	int		j;
	char	**dst;

	i = 0;
	j = 0;
	dst = malloc((wordscntr(s, c) + 1) * sizeof(char *));
	if (!dst)
		exit(1);
	dst = split_arrayer(dst, s, c, -1);
	return (dst);
}
