#include "../../../includes/mandatory/mini_shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int	has_quotes(const char *input)
{
	char	quotes;
	int		index;
	
	index = 0;
	quotes = '\0';
	while (input[index] != '\0')
	{
		if (input[index] == '"' || input[index] == '\'')
		{
			if (quotes == 0)
				quotes = input[index];
			else if (quotes == input[index])
				quotes = 0;
		}
		index++;
	}
	if (quotes)
		return (0);
	return (1);
}

static int	has_pipe(const char *input)
{
	int	index;
	int	dbquote;
	int	sgquote;
	int	is_valid;

	index = 0;
	dbquote = 0;
	sgquote = 0;
	is_valid = 0;
	if (input[index] == '|')
		return (0);
	while (input[index] != '\0')
	{
		if (input[index] == '\'')
			sgquote++;
		else if (input[index] == '"')
			dbquote++;
		if (input[index] == '|' && !(sgquote % 2) && !(dbquote %2))
		{
			if (is_valid)
				return (0);
			is_valid = 1;
		}
		else if (ft_isspace(input[index]))
			is_valid = 0;
		index++;
	}
	if (is_valid)
		return (0);
	return (1);
}

static int	has_redirect(char const *input)
{
	int	index;
	int	dbquote;
	int	sgquote;

	index = 0;
	dbquote = 0;
	sgquote = 0;
	while (input[index] != '\0')
	{
		if (input[index] == '\'')
			sgquote++;
		else if (input[index] == '"')
			dbquote++;
		if ((input[index] == '>' || input[index] == '<') && (sgquote % 2 == 0) && (dbquote % 2 == 0))
		{
			if (input[index] != input[index + 1])
			{
				if (ft_isspace(input[index + 1]) || ft_isalpha(input[index + 1]))
					return (1);
				else
					return (0);
			}
		}
		index++;
	}
	return (1);
}

int		initialize_checker(const char *prompt)
{
	if (!has_quotes(prompt))
		return (0);
	if (!has_pipe(prompt))
		return (0);
	if (!has_redirect(prompt))
		return (0);
	return (1);
}