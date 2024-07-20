#include "../../../includes/mandatory/mini_shell.h"

void	check_multi_cmd_right(t_tree *node, t_tree *current_prop)
{
	t_token	*current;
	t_token	*token;
	int		has_operator;

	current = node->right_token;
	has_operator = TRUE;
	token = node->right_token;
	while (current->next != NULL && current->content != NULL)
	{
		if (current->token != CMD_TOKEN)
			break ;
		current = current->next;
	}
	if (current->next == NULL || current->content == NULL)
		has_operator = TRUE;
	if (has_operator == TRUE)
	{
		while (token && token->content != NULL)
		{
			tree_build_nodes(token, &current_prop, TO_RIGHT);
			token = token->next;
		}
	}
}

void	check_multi_cmd_left(t_tree *node, t_tree *current_prop)
{
	t_token	*current;
	t_token	*token;
	int		has_operator;

	current = node->left_token;
	has_operator = TRUE;
	token = node->left_token;
	while (current->prev != NULL && current->content != NULL)
	{
		if (current->token != CMD_TOKEN)
			break ;
		current = current->prev;
	}
	if (current->prev == NULL || current->content == NULL)
		has_operator = TRUE;
	if (has_operator == TRUE)
	{
		while (token && token->content != NULL)
		{
			tree_build_nodes(token, &current_prop, TO_LEFT);
			token = token->prev;
		}
	}
}
