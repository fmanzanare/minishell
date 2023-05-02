#include "../../includes/minishell.h"

/**
 * Gets the string to be joined into cmd_arr.
 * If the string is between qmarks, joins everything.
 * If not, it joins until a redirection is found.
 * @param *str Full line to be checked.
 * @return String to be joined into cmd_arr.
*/
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

/**
 * Calculates the size of an array of strings.
 * @param **arr Used array to calculate its size.
 * @return Size of the received array.
*/
int	array_len(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len++;
	return (len);
}
