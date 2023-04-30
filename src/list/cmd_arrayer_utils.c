#include "../../includes/minishell.h"

char	*cmdjoin(char *str)
{
	char	*dst;
	int		i;
	int		qmarks[2];

	i = 0;
	dst = malloc(sizeof(char) * ft_strlen(str));
	if (!dst)
		exit(1);
	qmarks[0] = check_s_qmark(str[i], qmarks[0]);
	qmarks[1] = check_s_qmark(str[i], qmarks[1]);
	while (str[i] && (!ft_isredir(str[i])
			|| (ft_isredir(str[i]) && (qmarks[0] || qmarks[1]))))
	{
		qmarks[0] = check_s_qmark(str[i], qmarks[0]);
		qmarks[1] = check_s_qmark(str[i], qmarks[1]);
		dst[i] = str[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	array_len(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}
