#include "../../../includes/mandatory/mini_shell.h"
#include <stdlib.h>

t_venv	*env_lstnew(char *key, char *value)
{
	t_venv	*node;

	node = (t_venv *)malloc(sizeof(t_venv));
	if (node == NULL)
		return (NULL);
	if (key)
		node->key = ft_strdup(key);
	else
		node->key = NULL;
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

void	env_lstadd_back(t_venv **lst, t_venv *new)
{
	t_venv	*current;

	if (*lst == NULL && new != NULL)
	{
		*lst = new;
		return ;
	}
	if (new != NULL)
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

void	env_lstclear(t_venv **lst)
{
	t_venv	*current;
	t_venv	*next;

	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free (current->value);
		free (current->key);
		free (current);
			current = next;
	}
	*lst = NULL;
}

t_venv	*env_lstsearch(t_venv **lst, char *key)
{
	t_venv	*current;
	int			size;

	size = ft_strlen(key) + 1;
	current = *lst;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, key, size) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	env_size(t_venv **env)
{
	t_venv	*temp;
	int			len;

	if (!env || !*env)
		return (0);
	len = 0;
	temp = *env;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}
