#include "../../includes/minishell.h"

static void	refillstr(char *s, char *ret, char c)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			ret[i] = s[i];
			i++;
		}
	}
	ret[i] = c;
	ret[i + 1] = '\0';
}

char	*ft_charjoin(char *s, char c)
{
	char	*ret;
	int		len;

	if (s)
		len = ft_strlen(s);
	else
		len = 0;
	ret = NULL;
	if (c)
	{
		ret = malloc(sizeof(char) * (len + 2));
		if (!ret)
			exit(1);
		refillstr(s, ret, c);
	}
	return (ret);
}
