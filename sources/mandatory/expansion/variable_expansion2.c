/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 15:43:41 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/16 13:24:11 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../../includes/mandatory/mini_shell.h"

// char	*get_variable_name(const char **cursor)
// {
// 	size_t	name_length;
// 	char	*name;

// 	name_length = strcspn(*cursor, " $/\t\n,.'\"");
// 	name = strndup(*cursor, name_length);
// 	if (!name)
// 	{
// 		perror("malloc failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	*cursor += name_length;
// 	return (name);
// }

// void	append_value(char **expanded, const char *value)
// {
// 	*expanded = realloc(*expanded, strlen(*expanded) + strlen(value) + 1);
// 	if (!*expanded)
// 	{
// 		perror("realloc failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	strcat(*expanded, value);
// }

// void	append_variable_expanded(char **expanded, const char **cursor)
// {
// 	char	*name;
// 	char	*value;

// 	(*cursor)++;
// 	name = get_variable_name(cursor);
// 	value = expand_variable(name);
// 	free(name);
// 	if (value)
// 	{
// 		append_value(expanded, value);
// 		free(value);
// 	}
// }
