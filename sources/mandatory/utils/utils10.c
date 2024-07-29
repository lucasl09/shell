#include "../../../includes/mandatory/mini_shell.h"
#include <stdlib.h>

t_tree	*tree_new(char *content, t_tokens token_type)
{
	t_tree	*node;

	node = (t_tree *)malloc(sizeof(t_tree));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->tree_type = type_check(token_type);
	node->left = NULL;
	node->right = NULL;
	node->left_token = NULL;
	node->right_token = NULL;
	return (node);
}

void	treelst_clear(t_tree **lst)
{
	t_tree	*current;
	t_tree	*right;

	if (*lst == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		right = current->right;
		if (current->left != NULL)
			treelst_clear(&(current->left));
		if (current->content)
			free(current->content);
		free(current);
		current = right;
	}
	*lst = NULL;
}

void	tree_addleft(t_tree **lst, t_tree *new)
{
	t_tree	*last;

	last = NULL;
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->left != NULL)
		last = last->left;
	last->left = new;
	last->left_token = NULL;
}

void	tree_addright(t_tree **lst, t_tree *new)
{
	t_tree	*last;

	last = NULL;
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->right != NULL)
		last = last->right;
	last->right = new;
	last->right_token = NULL;
}

void	build_tnode(t_token *new_node, t_tree **tree_listed, int direction)
{
	t_tree	*new;

	new = tree_new(ft_strdup(new_node->content), new_node->token);
	if (direction == LEFT)
		tree_addleft(tree_listed, new);
	else
		tree_addright(tree_listed, new);
	free (new_node->content);
	new_node->content = NULL;
	new_node->token = NONE;
	return ;
}
