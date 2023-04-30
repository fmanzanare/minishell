#include "../../includes/minishell.h"

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

char	**pipe_spliter(char *s, char c)
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
