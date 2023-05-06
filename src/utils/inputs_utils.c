#include "../../includes/minishell.h"

/**
 * Checks if the raw line is empty (full of spaces, tabs, etc.)
 * @param *line Raw line
 * @return 1 if line is empty, 0 if line contains something.
*/
int	is_blank_line(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (line[i])
	{
		if (!ft_isspecialchar(line[i]))
			flag = 0;
		i++;
	}
	return (flag);
}

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
	{
		if (is_blank_line(line_splited[counter]))
			break ;
		counter++;
	}
	return (counter);
}
