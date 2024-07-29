/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roglopes <roglopes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:29:34 by roglopes          #+#    #+#             */
/*   Updated: 2024/07/14 16:31:57 by roglopes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/mandatory/mini_shell.h"

static void	insert_sorted(t_venv **sorted, t_venv *new_node)
{
	t_venv	*current;

	if (*sorted == NULL || ft_strncmp((*sorted)->key, new_node->key, \
		ft_strlen((*sorted)->key)) >= 0)
	{
		new_node->next = *sorted;
		*sorted = new_node;
	}
	else
	{
		current = *sorted;
		while (current->next && ft_strncmp(current->next->key, new_node->key, \
			ft_strlen(current->next->key)) < 0)
			current = current->next;
		new_node->next = current->next;
		current->next = new_node;
	}
}

static void	sort_env(t_venv **envp)
{
	t_venv	*sorted;
	t_venv	*current;
	t_venv	*next;

	current = *envp;
	sorted = NULL;
	while (current)
	{
		next = current->next;
		insert_sorted(&sorted, current);
		current = next;
	}
	*envp = sorted;
}

static t_venv	*copy_env(t_venv *origin)
{
	t_venv	*current;
	char		*key;
	char		*value;
	t_venv	*envp;

	current = origin;
	envp = NULL;
	while (current)
	{
		key = ft_strdup(current->key);
		if (current->value)
		{
			value = ft_strdup(current->value);
			env_lstadd_back(&envp, env_lstnew(key, value));
			free (value);
		}
		else
			env_lstadd_back(&envp, env_lstnew(key, NULL));
		free (key);
		current = current->next;
	}
	return (envp);
}

int	ft_envprints(t_venv *env)
{
	t_venv	*copy;

	copy = copy_env(env);
	sort_env(&copy);
	ft_env(&copy, TRUE);
	free_envp(&copy);
	return (0);
}
