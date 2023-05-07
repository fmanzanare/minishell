#include "../../includes/minishell.h"

void	parser(t_inputs *inputs, t_pipe *data)
{
	ft_expander(inputs, data);
	add_history(inputs->raw);
	free(inputs->raw);
	pipes_redirs_stringer(inputs);
	inputs->line_splited = deep_spliter(inputs->line, '|');
	inputs->lenght = input_size(inputs->line_splited);
	fill_command_lines(&inputs->args, inputs->line_splited, inputs);
	run_to_head(&inputs->args);
}
