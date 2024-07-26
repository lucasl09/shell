#include "../../../includes/mandatory/mini_shell.h"

static int	has_quotes(const char *input)
{
	char	quots;
	int		index;

	index = 0;
	quots = '\0';
	while (input[index] != '\0')
	{
		if (input[index] == '"' || input[index] == '\'')
		{
			if (quots == 0)
				quots = input[index];
			else if (quots == input[index])
				quots = 0;
		}
		index++;
	}
	if (quots)
		return (0);
	return (1);
}

static int	check_redirect(char const *input)
{
	int	double_q;
	int	single_q;

	double_q = 0;
	single_q = 0;
	while (*input != '\0')
	{
		if (*input == '\'')
			single_q++;
		else if (*input == '"')
			double_q++;
		if ((*input == '>' || *input == '<') && (single_q % 2 == 0)
			&& (double_q % 2 == 0))
		{
			if (*input != *(input + 1))
			{
				if (*(input + 1))
					return (1);
				else
					return (0);
			}
		}
		input++;
	}
	return (1);
}

int	verify_prompt(const char *input)
{
	if (!has_quotes(input))
		return (0);
	if (!check_pipe(input))
		return (0);
	if (!check_redirect(input))
		return (0);
	return (1);
}
