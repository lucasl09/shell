/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:29:34 by roglopes          #+#    #+#             */
/*   Updated: 2024/06/16 13:41:22 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

void	export_variable(t_token *tokens)
{
	char	*name;
	char	*value;
	t_token *current;

	name = NULL;
	value = NULL;
	current = tokens->next;

	if (current != NULL)
	{
		name = ft_strtok(current->content, "=");
		value = ft_strtok(NULL, "=");
		if (name != NULL)
		{
			if (value != NULL)
			{
				setenv(name, value, 1);
			}
			else
			{
				setenv(name, "", 1);
			}
		}
	}
	else
	{
		print_environment();
	}
}

int builtins(t_token *tokens)
{
    t_token *current;

    current = tokens;
    if (current == NULL || current->content == NULL)
        return (0);
    else if (ft_strcmp(current->content, "pwd") == 0 || ft_strcmp(current->content,
            "clear") == 0 || ft_strcmp(current->content, "exit") == 0
        || ft_strcmp(current->content, "cd") == 0 || ft_strcmp(current->content,
            "export") == 0 || ft_strcmp(current->content, "unset") == 0
        || ft_strcmp(current->content, "env") == 0 || ft_strcmp(current->content,
            "echo") == 0)
    {
        handle_internal_command(current);
        return (1);
    }
    return (0);
}