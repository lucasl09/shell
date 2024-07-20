#include "../../../includes/mandatory/mini_shell.h"

static void	for_additional_node(t_token *current, t_tree *current_prop)
{
	if (current->prev != NULL)
	{
		if (current->prev->prev == NULL || current->prev->prev->content == NULL)
			tree_build_nodes(current->prev, &current_prop, TO_LEFT);
		else
			current_prop->left_token = current->prev;
		if (current_prop->left_token)
			check_multi_cmd_left(current_prop, current_prop);
	}
	if (current->next != NULL)
	{
		if (current->next->next == NULL || current->next->next->content == NULL)
			tree_build_nodes(current->next, &current_prop, TO_RIGHT);
		else
			current_prop->right_token = current->next;
		if (current_prop->right_token)
			check_multi_cmd_right(current_prop, current_prop);
	}
}

t_tree	*break_nodes(t_token *current, t_tree **tree_lists, int direction)
{
	t_tree	*current_prop;

	current_prop = tree_new(ft_strdup(current->content), current->token);
	if (direction == TO_RIGHT)
		for_treeright(tree_lists, current_prop);
	else
		for_treeleft(tree_lists, current_prop);
	free(current->content);
	current->content = NULL;
	current->token = NONE;
	for_additional_node(current, current_prop);
	return (current_prop);
}

void	continue_division(t_tokens operator, t_tree **tree_lists,
		t_tree *current_prop, int direction)
{
	t_tree	*for_node;
	t_token	*current;

	for_node = NULL;
	if (direction == TO_RIGHT)
		current = last_token(current_prop->right_token);
	else
		current = current_prop->left_token;
	while (current != NULL && current->content != NULL)
	{
		if (current->token == operator)
		{
			for_node = break_nodes(current, &current_prop, direction);
			for_left_node(operator, for_node, tree_lists, TRUE);
			for_right_node(operator, for_node, tree_lists, TRUE);
		}
		else if (operator == 6 && current->token > 2)
		{
			for_node = break_nodes(current, &current_prop, direction);
			for_left_node(operator, for_node, tree_lists, TRUE);
		}
		else
			current = current->prev;
	}
}

void	for_left_node(t_tokens operator, t_tree *current_prop,
		t_tree **tree_lists, int status)
{
	if (status == FT_ERROR)
	{
		while (current_prop && current_prop->left != NULL)
			current_prop = current_prop->left;
	}
	if (current_prop->left != NULL || current_prop->left_token == NULL)
		return ;
	else if (current_prop->left_token)
	{
		if (current_prop->left_token->content == NULL)
			return ;
	}
	continue_division(operator, tree_lists, current_prop, TO_LEFT);
	if (current_prop->right_token)
		continue_division(operator, tree_lists, current_prop, TO_RIGHT);
}

void	for_right_node(t_tokens operator, t_tree *current_prop,
		t_tree **tree_lists, int status)
{
	if (status == FT_ERROR)
	{
		while (current_prop && current_prop->right != NULL)
			current_prop = current_prop->right;
	}
	if (current_prop->right != NULL
		|| current_prop->right_token == NULL)
		return ;
	else if (current_prop->right_token)
	{
		if (current_prop->right_token->content == NULL)
			return ;
	}
	continue_division(operator, tree_lists, current_prop, TO_RIGHT);
	if (current_prop->left_token)
		continue_division(operator, tree_lists, current_prop, TO_LEFT);
}
