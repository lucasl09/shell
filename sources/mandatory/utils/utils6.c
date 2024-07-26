#include "../../../includes/mandatory/mini_shell.h"

t_type_tree	initialize_checker(t_tokens token)
{
	t_type_tree	tree_type;

	if (token == WORD)
		tree_type = STRING;
	else if (token == CMD_TOKEN)
		tree_type = COMMAND;
	else if (token == FILE_TOKEN)
		tree_type = FILENAME;
	else if (token == DELIMITER_TOKEN)
		tree_type = DELIMITER;
	else
		tree_type = token + 11;
	return (tree_type);
}

void	verify_rightcmds(t_tree *node, t_tree *current_tree_node)
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
			initialize_treenode(token, &current_tree_node, RIGHT);
			token = token->next;
		}
	}
}

void	verify_leftcmds(t_tree *node, t_tree *current_tree_node)
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
			initialize_treenode(token, &current_tree_node, LEFT);
			token = token->prev;
		}
	}
}
