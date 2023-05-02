#include "../../includes/minishell.h"

/**
 * It copies the content of the received string into ret.
 * Then, it joins the received char and a null at the end.
 * @param *s String to be joined.
 * @param *ret String to be returned.
 * @param c Char to be joined into ret.
 * @return The received string with the char joined at the end.
*/
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

/**
 * Joins the received char into the received string.
 * @param *s String where the received char will be joined.
 * @param c Char to be joined into the received string.
 * @return New string after joining the received char.
*/
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
