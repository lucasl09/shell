/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:28:58 by roglopes          #+#    #+#             */
/*   Updated: 2024/07/13 18:20:24 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"
#include <stdio.h>
#include <unistd.h>

static void	get_content_init(char *content, int i, int start, char **final_line)
{
	char	*tmp;
	char	*line;

	line = ft_strndup(&(content[start]), i - start);
	tmp = ft_strjoin(*final_line, line);
	free(*final_line);
	free(line);
	*final_line = tmp;
}

static void	cquote(int *inquote, int *quote, int *i, char *content)
{
	if (*inquote == FT_ERROR)
	{
		*quote = content[(*i)++];
		*inquote = TRUE;
	}
	else
	{
		*inquote = FT_ERROR;
		(*i)++;
	}
}

static int	content_change(int inquote, int quote, int *i, char *content)
{
	int	start;

	if (inquote == TRUE)
	{
		start = *i;
		while (content[*i] && content[*i] != quote)
			(*i)++;
	}
	else
	{
		start = *i;
		while (content[*i] && content[*i] != '\'' && content[*i] != '\"')
			(*i)++;
	}
	return (start);
}

char	*remove_quotes_expansion(char *content)
{
	int		i;
	char	*final_line;
	int		inquote;
	int		quote;
	int		start;

	i = 0;
	final_line = NULL;
	inquote = FT_ERROR;
	quote = '\0';
	while (content[i])
	{
		if (((content[i] == '\'' || content[i] == '\"')
				&& inquote == FT_ERROR) || (inquote == TRUE
				&& content[i] == quote))
			cquote(&inquote, &quote, &i, content);
		else if ((inquote == TRUE && content[i] != quote)
			|| (inquote == FT_ERROR && content[i] != '\''
				&& content[i] != '\"'))
		{
			start = content_change(inquote, quote, &i, content);
			get_content_init(content, i, start, &final_line);
		}
	}
	return (final_line);
}