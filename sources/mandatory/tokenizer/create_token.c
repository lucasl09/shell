/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 23:33:24 by lluiz-de          #+#    #+#             */
/*   Updated: 2024/06/15 13:58:07 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

t_token	*token_for_redirect(int *i, char *cmd_line)
{
	t_token		*token;
	char		meta_c;

	if (cmd_line[*i] == '<' || cmd_line[*i] == '>')
		meta_c = cmd_line[*i];
	else
		return (NULL);

	if (cmd_line[*i] == meta_c)
	{
		if (cmd_line[(*i) + 1] == meta_c && cmd_line[(*i) + 2] == meta_c)
		{
			printf("Syntax error near unexpected token \'%c\'", meta_c);
			return (NULL);
		}
		else if (cmd_line[(*i) + 1] == meta_c)
			token = newtoken(ft_strndup(&cmd_line[(*i)++], 2), DLESS);
		else
			token = newtoken(ft_strndup(&cmd_line[*i], 1), LESS);
	}
	else
		token = NULL;
	return (token);
}

t_token	*is_word_token(int *i, char *cmd_line)
{
	t_token		*token;
	int			size;

	size = *i;
	while (ft_isspace(cmd_line[size]) == 0 && cmd_line[size])
		size++;
	token = newtoken(ft_strndup(&cmd_line[*i], size - *i), WORD);
	*i = size;
	return (token);
}

t_token	*token_expanded(int *i, char *cmd_line)
{
	t_token		*token;
	int			size;

	size = *i;
	size++;
	while (ft_isalpha(cmd_line[size]) != 0 || cmd_line[size] == '_')
		size++;
	token = newtoken(ft_strndup(&cmd_line[*i], size - *i), EXPANSION);
	*i = size;
	return (token);
}

t_token	*is_quote_token(int *i, char *cmd_line)
{
	t_token	*token;
	int			size;
	char		quote;

	size = *i;
	quote = cmd_line[size];
	size++;
	while (cmd_line[size] && cmd_line[size] != quote)
		size++;
	if (!cmd_line[size])
		return (NULL);
	else
		size++;
	token = newtoken(ft_strndup(&cmd_line[*i], size - *i), WORD);
	*i = size;
	return (token);
}

int	initialize_buildtoken(char *cmd_line, t_token **token_list)
{
	t_token		*token;
	int			i;

	i = 0;
	while (cmd_line[i])
	{
		token = NULL;
		if (cmd_line[i] == '<' || cmd_line[i] == '>')
		{
			token = token_for_redirect(&i, cmd_line);
			if (token == NULL)
				return (ERROR);
		}
		else if (cmd_line[i] == '|')
			token = newtoken(ft_strndup(&cmd_line[i], 1), PIPE);
		else if (cmd_line[i] == '$')
			token = token_expanded(&i, cmd_line);
		else if (cmd_line[i] == '\'' || cmd_line[i] == '\"')
		{
			token = is_quote_token(&i, cmd_line);
			if (token == NULL)
				return (ERROR);
		}
		else if (ft_isspace(cmd_line[i]) == 0)
			token = is_word_token(&i, cmd_line);
		if (token != NULL)
			token_to_back(token_list, token);
		if (cmd_line[i])
			i++;
	}
	return (TRUE);
}