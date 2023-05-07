/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deep_spliter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanzana <fmanzana@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 17:14:00 by fmanzana          #+#    #+#             */
/*   Updated: 2023/05/07 17:14:00 by fmanzana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Calculates the word length.
 * It doesn't take the qmarks.
 * @param *s String to work with.
 * @param c Split char.
 * @param start Starting index.
 * @param end Index of the new string end.
 * @return Word length.
*/
static int	wrd_len(char *s, char c, int start, int end)
{
	int	ret;

	ret = 0;
	while (start < end)
	{
		if (s[start] != '\'' && s[start] != '\"' && c != '|')
			ret++;
		else if (c == '|')
			ret++;
		start++;
	}
	return (ret);
}

/**
 * Get the string to be saved into the array.
 * @param *s String to work with.
 * @param start Starting index.
 * @param end Index of the new string end.
 * @return String to be added to the string array.
*/
static char	*stringmkr(char *s, char c, int start, int end)
{
	char	*wrd;
	int		i;

	i = 0;
	wrd = malloc((wrd_len(s, c, start, end) + 1) * sizeof(char));
	if (!wrd)
		exit(1);
	while (start < end)
	{
		if ((s[start] == '\'' || s[start] == '\"') && c != '|')
		{
			if (s[start + 1] == '\0')
				break ;
			start++;
		}
		wrd[i++] = s[start++];
	}
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
 * @return Array of string, spliting the received string by c.
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
		if (s[i] != c && idx < 0 && s[i] != '\"' && s[i] != '\'')
			idx = i;
		else if ((s[i] == c || i == ft_strlen(s)) && idx >= 0
			&& !qmarks[0] && !qmarks[1])
		{
			dst[j++] = stringmkr(s, c, idx, i);
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
