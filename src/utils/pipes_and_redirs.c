#include "../../includes/minishell.h"

static int	check_s_qmark(char c, int qmark_flag)
{
	if (c == '\'' && !qmark_flag)
		qmark_flag = 1;
	else if (c == '\'' && qmark_flag)
		qmark_flag = 0;
	return (qmark_flag);
}

static int	check_d_qmark(char c, int qmark_flag)
{
	if (c == '\"' && !qmark_flag)
		qmark_flag = 1;
	else if (c == '\"' && qmark_flag)
		qmark_flag = 0;
	return (qmark_flag);
}

static int	pipes_redirs_counter(char *str)
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

char	*pipes_redirs_stringer(char *str)
{
	int		s_qmark_flag;
	int		d_qmark_flag;
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	s_qmark_flag = 0;
	d_qmark_flag = 0;
	ret = malloc(sizeof(char) * pipes_redirs_counter(str));
	while (str[j])
	{
		s_qmark_flag = check_s_qmark(str[j], s_qmark_flag);
		d_qmark_flag = check_d_qmark(str[j], d_qmark_flag);
		//-----------------------------------------------------
		/* DIVIDIR ESTOS "IF" EN UNA FUNCION CHECKER */
		if (str[j] == '|' && !s_qmark_flag && !d_qmark_flag)
		{
			ret[i] = str[j];
			i++;
		}
		else if (str[j] == '>' && str[j + 1] != '>' && !s_qmark_flag
			&& !d_qmark_flag)
		{
			ret[i] = str[j];
			i++;
		}
		else if (str[j] == '<' && str[j + 1] != '<' && !s_qmark_flag
			&& !d_qmark_flag)
		{
			ret[i] = str[j];
			i++;
		}
		//-----------------------------------------------------
		j++;
	}
	ret[i] = '\0';
	return (ret);
}

// FUNCION TEMPORAL PARA VERIFICAR QUE FUNCIONA CORRECTAMENTE.
void	print_pipes_redirs_str(char *line)
{
	int		i;
	char	*str;

	i = 0;
	str = pipes_redirs_stringer(line);
	while (str[i])
	{
		ft_printf("%c", str[i]);
		i++;
	}
	ft_printf("\n");
}
