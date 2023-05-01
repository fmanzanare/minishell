#include "../../includes/minishell.h"

static char	*expand_var(char *var, t_env *env, int var_len, t_inputs *inputs)
{
	char	*ret;
	t_env	*aux;
	int		j;
	int		len;

	aux = env;
	j = 0;
	len = 0;
	if (var[0] != '?')
	{
		while (aux->next && !ft_strnstr(aux->line, var, var_len))
		{
			aux = aux->next;
			if (!aux->next)
				return (NULL);
		}
		j = ft_strlen(var);
		while (aux->line[(j++)])
			len++;
		ret = ft_substr(aux->line, var_len, len);
	}
	else
		ret = ft_itoa(inputs->exst);
	return (ret);
}

static void	get_expvar(t_inputs *inputs, t_env *env, int *e_idx)
{
	int		i;
	int		var_len;
	char	*var;
	char	*var_cnt;

	var_len = 0;
	i = (*e_idx) + 1;
	while (inputs->raw[i] != ' ' && inputs->raw[i] != '\"'
		&& inputs->raw[i] != '\'' && inputs->raw[i])
	{
		var_len++;
		i++;
	}
	i = (*e_idx) + 1;
	var = ft_substr(inputs->raw, i, var_len);
	var = ft_charjoin(var, '=');
	var_len++;
	*e_idx += (ft_strlen(var) - 1);
	var_cnt = expand_var(var, env, var_len, inputs);
	if (!var_cnt)
		return ;
	inputs->line = ft_strjoin(inputs->line, var_cnt);
}

void	ft_expander(t_inputs *inputs, t_env *env)
{
	int		i;
	int		qmarks[2];

	i = 0;
	qmarks[0] = 0;
	qmarks[1] = 0;
	while (inputs->raw[i])
	{
		qmarks[0] = check_s_qmark(inputs->raw[i], qmarks[0]);
		if (!qmarks[0])
			qmarks[1] = check_d_qmark(inputs->raw[i], qmarks[1]);
		if (inputs->raw[i] == '$' && (!qmarks[0]
				|| (qmarks[0] && qmarks[1])))
		{
			get_expvar(inputs, env, &i);
			i++;
			if (!inputs->raw[i])
				break ;
		}
		inputs->line = ft_charjoin(inputs->line, inputs->raw[i]);
		i++;
	}
}
