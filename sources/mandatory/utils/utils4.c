#include "../../../includes/mandatory/mini_shell.h"

static void	add_ast_node(t_token *current, t_tree *current_tree_node)
{
	if (current->prev != NULL)
	{
		if (current->prev->prev == NULL || current->prev->prev->content == NULL)
			initialize_treenode(current->prev, &current_tree_node, LEFT);
		else
			current_tree_node->left_token = current->prev;
		if (current_tree_node->left_token)
			verify_leftcmds(current_tree_node, current_tree_node);
	}
	if (current->next != NULL)
	{
		if (current->next->next == NULL || current->next->next->content == NULL)
			initialize_treenode(current->next, &current_tree_node, RIGHT);
		else
			current_tree_node->right_token = current->next;
		if (current_tree_node->right_token)
			verify_rightcmds(current_tree_node, current_tree_node);
	}
}

t_tree	*break_nodes(t_token *current, t_tree **tree_lists, int direction)
{
	t_tree	*current_tree_node;

	current_tree_node = tree_new(ft_strdup(current->content), current->token);
	if (direction == RIGHT)
		tree_addright(tree_lists, current_tree_node);
	else
		tree_addleft(tree_lists, current_tree_node);
	free(current->content);
	current->content = NULL;
	current->token = NONE;
	add_ast_node(current, current_tree_node);
	return (current_tree_node);
}

void	continue_division(t_tokens operator, t_tree **tree_lists,
		t_tree *ast_current_node, int direction)
{
	t_tree	*node_ast;
	t_token	*current;

	node_ast = NULL;
	if (direction == RIGHT)
		current = verify_lastlst(ast_current_node->right_token);
	else
		current = ast_current_node->left_token;
	while (current != NULL && current->content != NULL)
	{
		if (current->token == operator)
		{
			node_ast = break_nodes(current, &ast_current_node, direction);
			for_left_cnodes(operator, node_ast, tree_lists, TRUE);
			for_right_cnodes(operator, node_ast, tree_lists, TRUE);
		}
		else if (operator == 6 && current->token > 2)
		{
			node_ast = break_nodes(current, &ast_current_node, direction);
			for_left_cnodes(operator, node_ast, tree_lists, TRUE);
		}
		else
			current = current->prev;
	}
}

void	for_left_cnodes(t_tokens operator, t_tree *ast_current_node,
		t_tree **tree_lists, int status)
{
	if (status == FALSE)
	{
		while (ast_current_node && ast_current_node->left != NULL)
			ast_current_node = ast_current_node->left;
	}
	if (ast_current_node->left != NULL || ast_current_node->left_token == NULL)
		return ;
	else if (ast_current_node->left_token)
	{
		if (ast_current_node->left_token->content == NULL)
			return ;
	}
	continue_division(operator, tree_lists, ast_current_node, LEFT);
	if (ast_current_node->right_token)
		continue_division(operator, tree_lists, ast_current_node, RIGHT);
}

void	for_right_cnodes(t_tokens operator, t_tree *ast_current_node,
		t_tree **tree_lists, int status)
{
	if (status == FALSE)
	{
		while (ast_current_node && ast_current_node->right != NULL)
			ast_current_node = ast_current_node->right;
	}
	if (ast_current_node->right != NULL
		|| ast_current_node->right_token == NULL)
		return ;
	else if (ast_current_node->right_token)
	{
		if (ast_current_node->right_token->content == NULL)
			return ;
	}
	continue_division(operator, tree_lists, ast_current_node, RIGHT);
	if (ast_current_node->left_token)
		continue_division(operator, tree_lists, ast_current_node, LEFT);
}
