#include "../../../includes/mandatory/mini_shell.h"

void	initialize_node(t_token *new_node, t_tree **lists, int mode)
{
	t_tree	*new;

	new = ast_new(ft_strdup(new_node->content), new_node->token);
	if (mode == TO_LEFT)
		tree_add_left(lists, new);
	else
		tree_add_right(lists, new);
	return ;
}

t_tree	*break_nodes(t_token *current, t_tree **lists, int mode)
{
	t_tree	*current_tree_node;

	current_tree_node = tree_new(ft_strdup(current->content), current->token);

	if (mode == FALSE)
		tree_add_right(lists, current_tree_node);
	else
		tree_add_left(lists, current_tree_node);

	free (current->content);
	current->content = NULL;
	current->token = NONE;

	if (current->prev != NULL)
	{
		if (current->prev->prev == NULL || current->prev->prev->token == NONE)
			initialize_node(current->prev, &current_tree_node, TO_LEFT);
		else
			current_tree_node->left_token = current->prev;
	}
	if (current->next != NULL)
	{
		if (current->next->next == NULL || current->next->next->token == NONE)
			initialize_node(current->next, &current_tree_node, TO_RIGHT);
		else
			current_tree_node->right_token = current->next;
	}
	return (current_tree_node);
}

void	for_left_node(tokens opr, t_tree *nodes_in_exec, t_tree **lists)
{
	t_tree	*ident_node;
	t_token	*current;

	if (nodes_in_exec->left != NULL || nodes_in_exec->left_token == NULL)
		return;

	current = nodes_in_exec->left_token;
	while (current != NULL)
	{
		if (current->token == opr)
		{
			ident_node = break_nodes(current, lists, TRUE);
			for_left_node(opr, ident_node, lists);
			for_right_node(opr, ident_node, lists);
		}
		else
			current = current->prev;
	}
}

void	for_right_node(tokens opr, t_tree *nodes_in_exec, t_tree **lists)
{
	t_tree	*ident_node;
	t_token	*current;

	if (nodes_in_exec->right != NULL || nodes_in_exec->right_token == NULL)
		return;

	current = nodes_in_exec->right_token;
	while (current != NULL)
	{
		if (current->token == opr)
		{
			ident_node = break_nodes(current, lists, FALSE);
			for_left_node(opr, ident_node, lists);
			for_right_node(opr, ident_node, lists);
		}
		else
			current = current->next;
	}
}

int	planting_tree(t_token **token_list, tokens opr, t_tree **lists)
{
	t_token	*current;

	current = last_token(*token_list);
	while (current->prev != NULL)
	{
		if (current->token == opr)
		{
			break_nodes(current, lists, 0);
			return (TRUE) ;
		}
		else
			current = current->prev;
	}
	return (FALSE);
}

void	eotokens(t_token **token_list, t_tree **lists)
{
	t_token		*current;
	int			opr;
	int			start;

	current = last_token(*token_list);
	opr = PIPE;
	start = FALSE;
	if (current->prev == NULL)
	{
		initialize_node(current, lists, TO_LEFT);
		return ;
	}
	while (opr > 3)
	{
		start = planting_tree(token_list, opr, lists);
		if (start == FALSE)
			opr--;
		else
			break ;
	}
	if (start == TRUE)
	{
		while (opr > 3)
		{
			for_left_node(opr, *lists, lists);
			for_right_node(opr, *lists, lists);
			opr--;
		}
	}
}