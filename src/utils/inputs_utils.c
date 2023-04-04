#include "../../includes/minishell.h"

/**
 * Mesures the length of the splited line received from inputs.
 * @param **line_splited line splited by pipes '|'.
 * @return lenght of the splited line.
*/
int	input_size(char **line_splited)
{
	int		counter;

	counter = 0;
	while (line_splited[counter])
		counter++;
	return (counter);
}
