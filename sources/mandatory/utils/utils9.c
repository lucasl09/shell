#include "../../../includes/mandatory/mini_shell.h"

static void	add_tnode(t_token *current, t_tree *current_tnode)
{
	if (current->prev != NULL)
	{
		if (current->prev->prev == NULL || current->prev->prev->content == NULL)
			build_tnode(current->prev, &current_tnode, LEFT);
		else
			current_tnode->left_token = current->prev;
		if (current_tnode->left_token)
			has_left_cmds(current_tnode, current_tnode);
	}
	if (current->next != NULL)
	{
		if (current->next->next == NULL || current->next->next->content == NULL)
			build_tnode(current->next, &current_tnode, RIGHT);
		else
			current_tnode->right_token = current->next;
		if (current_tnode->right_token)
			has_right_cmds(current_tnode, current_tnode);
	}
}

t_tree	*cut_all(t_token *current, t_tree **tree_listed, int direction)
{
	t_tree	*current_tnode;

	current_tnode = tree_new(ft_strdup(current->content), current->token);
	if (direction == RIGHT)
		tree_addright(tree_listed, current_tnode);
	else
		tree_addleft(tree_listed, current_tnode);
	free(current->content);
	current->content = NULL;
	current->token = NONE;
	add_tnode(current, current_tnode);
	return (current_tnode);
}

void	still_cut(t_tokens opr, t_tree **tree_listed,
		t_tree *current_node_in, int direction)
{
	t_tree	*node_ast;
	t_token	*current;

	node_ast = NULL;
	if (direction == RIGHT)
		current = token_lstlast(current_node_in->right_token);
	else
		current = current_node_in->left_token;
	while (current != NULL && current->content != NULL)
	{
		if (current->token == opr)
		{
			node_ast = cut_all(current, &current_node_in, direction);
			cut_tleft(opr, node_ast, tree_listed, TRUE);
			cut_tright(opr, node_ast, tree_listed, TRUE);
		}
		else if (opr == 6 && current->token > 2)
		{
			node_ast = cut_all(current, &current_node_in, direction);
			cut_tleft(opr, node_ast, tree_listed, TRUE);
		}
		else
			current = current->prev;
	}
}

void	cut_tleft(t_tokens opr, t_tree *current_node_in,
		t_tree **tree_listed, int status)
{
	if (status == FALSE)
	{
		while (current_node_in && current_node_in->left != NULL)
			current_node_in = current_node_in->left;
	}
	if (current_node_in->left != NULL || current_node_in->left_token == NULL)
		return ;
	else if (current_node_in->left_token)
	{
		if (current_node_in->left_token->content == NULL)
			return ;
	}
	still_cut(opr, tree_listed, current_node_in, LEFT);
	if (current_node_in->right_token)
		still_cut(opr, tree_listed, current_node_in, RIGHT);
}

void	cut_tright(t_tokens opr, t_tree *current_node_in,
		t_tree **tree_listed, int status)
{
	if (status == FALSE)
	{
		while (current_node_in && current_node_in->right != NULL)
			current_node_in = current_node_in->right;
	}
	if (current_node_in->right != NULL
		|| current_node_in->right_token == NULL)
		return ;
	else if (current_node_in->right_token)
	{
		if (current_node_in->right_token->content == NULL)
			return ;
	}
	still_cut(opr, tree_listed, current_node_in, RIGHT);
	if (current_node_in->left_token)
		still_cut(opr, tree_listed, current_node_in, LEFT);
}
