#include "../../../includes/mandatory/mini_shell.h"

t_token	*newtoken(char *content, t_tokens type)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->token = type;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	token_to_back(t_token **lst, t_token *new)
{
	t_token	*current;

	if (*lst == NULL && new != NULL)
	{
		*lst = new;
		return ;
	}
	if (new != NULL)
	{
		current = *lst;
		if (current != NULL)
		{
			while (current->next != NULL)
				current = current->next;
			current->next = new;
			new->prev = current;
		}
		else
			*lst = new;
	}
}

t_token	*last_token(t_token *lst)
{
	if (lst)
	{
		while (lst->next && lst->next->token != NONE)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}
