/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:28:58 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/15 15:43:57 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../../includes/mandatory/mini_shell.h"

// char	*expand_variable(const char *variable)
// {
// 	char	*value;
// 	char	*expanded_value;

// 	value = getenv(variable);
// 	if (value)
// 	{
// 		expanded_value = strdup(value);
// 		if (!expanded_value)
// 		{
// 			perror("strdup failed");
// 			return (NULL);
// 		}
// 		return (expanded_value);
// 	}
// 	return (NULL);
// }

// void	append_char_expanded(char **expanded, const char **cursor)
// {
// 	size_t	current_length;

// 	current_length = ft_strlen(*expanded);
// 	*expanded = realloc(*expanded, current_length + 2);
// 	if (!*expanded)
// 	{
// 		perror("realloc failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	(*expanded)[current_length] = **cursor;
// 	(*expanded)[current_length + 1] = '\0';
// 	(*cursor)++;
// }

// void	expand_token(t_token *token)
// {
// 	const char	*cursor;
// 	char		*expanded;

// 	cursor = token->content;
// 	expanded = malloc(ft_strlen(token->content) + 1);
// 	if (!expanded)
// 	{
// 		perror("malloc failed");
// 		return ;
// 	}
// 	expanded[0] = '\0';
// 	while (*cursor)
// 	{
// 		if (*cursor == '$')
// 		{
// 			append_variable_expanded(&expanded, &cursor);
// 		}
// 		else
// 		{
// 			append_char_expanded(&expanded, &cursor);
// 		}
// 	}
// 	free(token->content);
// 	token->content = expanded;
// }

// void	expand_variables_tokens(t_token *head)
// {
// 	t_token	*current;

// 	current = head;
// 	while (current)
// 	{
// 		expand_token(current);
// 		current = current->next;
// 	}
// }
