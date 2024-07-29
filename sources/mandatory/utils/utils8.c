#include "../../../includes/mandatory/mini_shell.h"
#include <fcntl.h>

t_types_tree	type_check(t_tokens token)
{
	t_types_tree	tree_type;

	if (token == WORD)
		tree_type = STRING;
	else if (token == CMD_TOKEN)
		tree_type = COMMAND;
	else if (token == FTOKEN)
		tree_type = FILENAME;
	else if (token == DTOKEN)
		tree_type = DELIMITER;
	else
		tree_type = token + 11;
	return (tree_type);
}

void	has_right_cmds(t_tree *node, t_tree *current_tnode)
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
		has_operator = FALSE;
	if (has_operator == FALSE)
	{
		while (token && token->content != NULL)
		{
			build_tnode(token, &current_tnode, RIGHT);
			token = token->next;
		}
	}
}

void	has_left_cmds(t_tree *node, t_tree *current_tnode)
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
		has_operator = FALSE;
	if (has_operator == FALSE)
	{
		while (token && token->content != NULL)
		{
			build_tnode(token, &current_tnode, LEFT);
			token = token->prev;
		}
	}
}
