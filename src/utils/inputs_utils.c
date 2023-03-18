#include "../../includes/minishell.h"

int		input_size(char **line_splited)
{
	int		counter;

	counter = 0;
	while (line_splited[counter])
		counter++;
	return (counter);
}
