/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:10:28 by roglopes          #+#    #+#             */
/*   Updated: 2024/07/13 16:52:08 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

static int	has_quotes_in(const char *input)
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

static int	has_redirect_in(char const *input)
{
	int	dbq;
	int	sgq;

	dbq = 0;
	sgq = 0;
	while (*input != '\0')
	{
		if (*input == '\'')
			sgq++;
		else if (*input == '"')
			dbq++;
		if ((*input == '>' || *input == '<') && (sgq % 2 == 0)
			&& (dbq % 2 == 0))
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

int	all_checked(const char *input)
{
	if (!has_quotes_in(input))
		return (0);
	if (!has_pipe_in(input))
		return (0);
	if (!has_redirect_in(input))
		return (0);
	return (1);
}
